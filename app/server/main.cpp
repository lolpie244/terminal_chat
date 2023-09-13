#include <csignal>
#include <iostream>

#include "networking/communication_socket.h"
#include "networking/connection_socket.h"

void wait_message(char* message, const tcp_socket::CommunicationSocket& socket)
{
	std::cout << "SOME MESSAGE " << message;
}

void func(tcp_socket::CommunicationSocket socket)
{
	socket.send("help");
	socket.on_recieve(wait_message, false);
	std::cout << "SOME FUNC";
}
int main(){
	tcp_socket::ConnectionSocket socket("2346");
	socket.listen(func);
}
