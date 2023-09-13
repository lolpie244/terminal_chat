#include <functional>
#include <iostream>
#include <memory>
#include <netdb.h>
#include <sstream>
#include <string>
#include <sys/socket.h>

#include "communication_socket.h"

namespace tcp_socket
{
using std::string, std::stringstream;

CommunicationSocket::CommunicationSocket(int socket_fd, sockaddr_storage address,
        bool is_server)
	: socket_fd(socket_fd), address(address), is_server(is_server) {}

void CommunicationSocket::send(const char *message) const
{
	// TODO: set proper size
	::send(socket_fd, message, 1024, 0);
}

void CommunicationSocket::send(const stringstream &message) const
{
	send(message.str().c_str());
}

void CommunicationSocket::send(const string &message) const
{
	send(message.c_str());
}


void CommunicationSocket::on_recieve(
    std::function<void(char *message, const CommunicationSocket& socket)> callback_function,
    bool always)
{
	// TODO: run in different thread
	do {
		// TODO: set proper size
		char *buffer = new char[1024];
		::recv(socket_fd, buffer, 1024, 0);
		callback_function(buffer, *this);
	} while (always);
}

void CommunicationSocket::on_recieve(std::function<void(stringstream &message, const CommunicationSocket& address)> callback_function, bool always)
{
	on_recieve(
	[callback_function](char *buffer, const CommunicationSocket& socket) {
		stringstream message(buffer);
		delete[] buffer;
		callback_function(message, socket);
	},
	always);
}

void CommunicationSocket::on_recieve(std::function<void(string &message, const CommunicationSocket& address)> callback_function, bool always)
{
	on_recieve(
	[callback_function](char *buffer, const CommunicationSocket& socket) {
		string message(buffer);
		delete[] buffer;
		callback_function(message, socket);
	},
	always);
}

CommunicationSocket::~CommunicationSocket(){
	if (is_server)
		::shutdown(socket_fd, 2);
}
} // namespace tcp_socket
