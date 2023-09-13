#include "chat/user/user.h"
#include "networking/communication_socket.h"
#include "networking/connection_socket.h"
#include "utils/events.h"
#include <cstdio>
#include <cstring>
#include <iostream>

#include <ndbm.h>
#include <netdb.h>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <thread>

int main()
{
	int flag = 1;

	addrinfo hints = tcp_socket::ConnectionSocket::get_default_addrinfo();
	hints.ai_family = AF_INET6;
	hints.ai_flags = AI_PASSIVE;

	tcp_socket::ConnectionSocket socket(nullptr, "2348", hints);

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
	[](tcp_socket::CommunicationSocket socket) {
		while (true)
			socket.on_recieve(
			[](std::stringstream &message, tcp_socket::CommunicationSocket socket) {
				int event;
				message >> event;
				message.ignore();
				if(event == events::CLIENT_NEW_MESSAGE)
				{
					std::string text;
					getline(message, text, '\0');
					std::cout << text << std::endl;
				}
			});
	},
	new_socket);

	getchar();
	write_thread = std::thread(
	[](tcp_socket::CommunicationSocket socket, user::User current_user) {
		std::string message;
		while (true) {
			std::getline(std::cin, message);
			std::stringstream s;
			s << current_user << " > " << message;
			std::cout << "\x1b[A\r" << s.str() << std::endl;
			socket.send(
			    events::add_event_prefix(s.str(), events::SERVER_NEW_MESSAGE));
		}
	},
	new_socket, current_user);

	read_thread.join();
	write_thread.join();
}
