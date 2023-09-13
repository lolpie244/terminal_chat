#include <csignal>
#include <iostream>
#include <sstream>
#include <string>

#include "chat/chat/chat.h"
#include "networking/communication_socket.h"
#include "networking/connection_socket.h"
#include "utils/events.h"

void recieve_message(std::stringstream &message,
                     tcp_socket::CommunicationSocket socket,
                     chat::Chat &current_chat)
{
	int event;
	message >> event;

	std::string formated_message;
	message.ignore(1);
	std::getline(message, formated_message, '\0');

	switch (event) {
	case events::SERVER_CONNECTION_ATTEMPT:
		current_chat.add_user(socket, formated_message);
		break;
	case events::SERVER_NEW_MESSAGE:
		std::cout << formated_message << '\n';
		current_chat.new_message(socket, formated_message);
		break;
	}
}

int main()
{
	tcp_socket::ConnectionSocket socket("2348");
	chat::Chat current_chat("test", "1234");
	socket.listen([&current_chat](tcp_socket::CommunicationSocket socket) {
		while (true)
			socket.on_recieve(
				[&current_chat](std::stringstream &message, tcp_socket::CommunicationSocket socket) {
					recieve_message(message, socket, current_chat);
				}
			);
	});
}
