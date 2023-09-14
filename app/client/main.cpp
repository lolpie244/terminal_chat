#include "chat/user/user.h"
#include "networking/communication_socket.h"
#include "networking/connection_socket.h"
#include "utils/events.h"
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>

#include <ndbm.h>
#include <netdb.h>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

#include "utils/terminal.h"
#include "utils/config.h"

void write_message(tcp_socket::CommunicationSocket socket,
                   user::User &current_user)
{
	terminal::BufferToggle bt;

	bt.off();
	while (true) {
		char c;
		do {
			c = std::getchar();
			current_user.current_text += c;
		} while (c != '\n');

		std::stringstream s;
		s << current_user << " > " << current_user.current_text;
		current_user.current_text = "";

		std::cout << terminal::LINE_UP << terminal::BEGIN << s.str() << std::flush;
		socket.send(events::add_event_prefix(s.str(), events::SERVER_NEW_MESSAGE));
	}
	bt.on();
}

void read_message(std::stringstream &message,
                  tcp_socket::CommunicationSocket socket,
                  const user::User &current_user)
{
	int event;
	message >> event;
	message.ignore();
	if (event == events::CLIENT_NEW_MESSAGE) {
		std::string text;
		getline(message, text, '\0');
		if (current_user.current_text.length() != 0)
			std::cout << terminal::CLEAR_LINE << terminal::BEGIN << std::flush;

		std::cout << text << current_user.current_text << std::flush;
	}
}

int main()
{
	int flag = 1;

	addrinfo hints = tcp_socket::ConnectionSocket::get_default_addrinfo();
	hints.ai_family = AF_INET6;
	hints.ai_flags = AI_PASSIVE;

	tcp_socket::ConnectionSocket socket(nullptr, config::PORT, hints);

	std::cout << "Connection to server in progress\n";
	auto new_socket = socket.connect();

	std::string username, chat_name, password;

	std::cout << "Connection established.\nChat name: ";
	std::cin >> chat_name;
	std::cout << "\nPassword: ";
	std::cin >> password;

	new_socket.send(
	    events::add_event_prefix(password, events::SERVER_CONNECTION_ATTEMPT));

	new_socket.on_recieve(
	[](std::string &result, tcp_socket::CommunicationSocket socket) {
		if (std::stoi(result) != events::CLIENT_CONNECTED) {
			std::cout << ("Incorrect chat name or password");
			exit(0);
		}
	});

	std::cout << "\nUsername: ";
	std::cin >> username;
	user::User current_user(username);

	std::thread read_thread, write_thread;

	read_thread = std::thread(
	                  [](tcp_socket::CommunicationSocket socket,
	const user::User &current_user) {
		bool recieve_successful;
		do {
			recieve_successful = socket.on_recieve(
				[&current_user](std::stringstream &message,
				tcp_socket::CommunicationSocket socket) {
				read_message(message, socket, current_user);
			});
		} while (recieve_successful);
	},
	new_socket, std::cref(current_user));

	getchar();
	write_thread = std::thread(write_message, new_socket, std::ref(current_user));

	read_thread.join();
	write_thread.join();
}
