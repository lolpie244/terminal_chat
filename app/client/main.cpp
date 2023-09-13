#include "networking/communication_socket.h"
#include "networking/connection_socket.h"
#include <cstring>
#include <iostream>

#include <ndbm.h>
#include <netdb.h>
#include <sys/socket.h>

void func(char* message, const tcp_socket::CommunicationSocket& socket) {
	socket.send("MEEE");
	std::cout << message;
}
int main()
{
	addrinfo hints = tcp_socket::ConnectionSocket::get_default_addrinfo();
	hints.ai_family = AF_INET6;
	hints.ai_flags = AI_PASSIVE;

	tcp_socket::ConnectionSocket socket(nullptr, "2346", hints);

	auto new_socket = socket.connect();
	new_socket.on_recieve(func, false);
}
