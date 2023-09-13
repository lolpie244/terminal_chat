#pragma once

#include "networking/communication_socket.h"
#include <string>
#include <list>
#include <memory>
// #include <sys/socket.h>

namespace chat {
	using std::string;
	using std::weak_ptr;

	class Chat {
	private:
		string password;
		string name;
		std::list<tcp_socket::CommunicationSocket> sockets;
		// std::list<tcp_socket::CommunicationSocket> user_list;
	public:
		Chat(string name, string password);

		void add_user(tcp_socket::CommunicationSocket& socket, string password);
		void new_message(const tcp_socket::CommunicationSocket& socket, const string& message);
	};
}
