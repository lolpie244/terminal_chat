#include <functional>
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

void CommunicationSocket::send(const char *message)
{
	// TODO: set proper size
	::send(socket_fd, message, 1024, 0);
}

void CommunicationSocket::send(const stringstream &message)
{
	send(message.str().c_str());
}

void CommunicationSocket::send(const string &message)
{
	send(message.c_str());
}


void CommunicationSocket::on_recieve(
    std::function<void(char *message, sockaddr_storage address)> callback_function,
    bool always)
{
	// TODO: run in different thread
	do {
		// TODO: set proper size
		char *buffer = new char[1024];
		::recv(socket_fd, buffer, 1024, 0);
		callback_function(buffer, address);
	} while (always);
}

void CommunicationSocket::on_recieve(std::function<void(stringstream &message, sockaddr_storage address)> callback_function, bool always)
{
	on_recieve(
	[callback_function](char *buffer, sockaddr_storage address) {
		stringstream message(buffer);
		delete[] buffer;
		callback_function(message, address);
	},
	always);
}

void CommunicationSocket::on_recieve(std::function<void(string &message, sockaddr_storage address)> callback_function, bool always)
{
	on_recieve(
	[callback_function](char *buffer, sockaddr_storage address) {
		string message(buffer);
		delete[] buffer;
		callback_function(message, address);
	},
	always);
}
} // namespace tcp_socket
