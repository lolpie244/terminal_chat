#include "chat.h"
#include "networking/communication_socket.h"
#include <iostream>
#include "utils/events.h"
#include <string>

namespace chat {
	Chat::Chat(string name, string password): name(name), password(password){}

	void Chat::add_user(const tcp_socket::CommunicationSocket& client_socket, string password)
	{
		if (password != this->password)
		{
			client_socket.send(events::add_event_prefix("", events::CLIENT_CONNECTION_REFUSED));	
			return;
		}
		sockets.push_back(client_socket);
		client_socket.send(std::to_string(events::CLIENT_CONNECTED));	
	}

	void Chat::new_message(const tcp_socket::CommunicationSocket& author, const string& message) {
		string complete_message = events::add_event_prefix(message, events::CLIENT_NEW_MESSAGE);
		for(auto& socket: sockets) {
			if (socket != author)
				socket.send(complete_message);
		}
	}
}
