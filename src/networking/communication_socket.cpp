#include <cerrno>
#include <cstring>
#include <string.h>
#include <functional>
#include <iostream>
#include <memory>
#include <netdb.h>
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <vector>

#include "communication_socket.h"

namespace tcp_socket
{
using std::string, std::stringstream;

CommunicationSocket::CommunicationSocket(int socket_fd, sockaddr_storage address,
        bool is_server)
	: socket_fd(socket_fd), address(address), is_server(is_server) {}

bool CommunicationSocket::operator==(const CommunicationSocket& other_socket)
{
	return socket_fd == other_socket.socket_fd;
}

void CommunicationSocket::close_connection() const
{
	::close(socket_fd);
}

void CommunicationSocket::send(const char *message) const
{
	// TODO: set proper size
	int send_size;
	send_size = ::send(socket_fd, message, 1024, 0);
	if (send_size == -1){
		std::cout << "Send error: " << strerror(errno);
		return;
	}

}

void CommunicationSocket::send(stringstream &message) const
{
	string next_message;
	std::getline(message, next_message, '\0');
	send(next_message.c_str());
}

void CommunicationSocket::send(const string &message) const
{
	send(message.c_str());
}
std::vector<std::thread> recieve_threads;
void CommunicationSocket::on_recieve(
    std::function<void(char *message, const CommunicationSocket& socket)> callback_function)
{
	// TODO: set proper size
	char *buffer = new char[1024];
	int size = 1024;
	int recieve_size =::recv(socket_fd, buffer, size, 0); 
	if(recieve_size == -1) {
		delete[] buffer;
		return;
	}

	// recieve_threads.emplace_back(callback_function, buffer, *this);
	callback_function(buffer, *this);
}

void CommunicationSocket::on_recieve(std::function<void(stringstream &message, const CommunicationSocket& address)> callback_function)
{
	on_recieve(
	[callback_function](char *buffer, const CommunicationSocket& socket) {
		stringstream message(buffer);
		callback_function(message, socket);
	});
}

void CommunicationSocket::on_recieve(std::function<void(string &message, const CommunicationSocket& address)> callback_function)
{
	on_recieve(
	[callback_function](char *buffer, const CommunicationSocket& socket) {
		string message(buffer);
		callback_function(message, socket);
	});
}

CommunicationSocket::~CommunicationSocket(){
	// if (is_server)
	// 	::close(socket_fd);
}
} // namespace tcp_socket
