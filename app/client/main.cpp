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
	addrinfo hints;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	tcp_socket::ConnectionSocket socket(nullptr, "2346", hints);

	auto new_socket = socket.connect();
	new_socket.on_recieve(func, false);
}
