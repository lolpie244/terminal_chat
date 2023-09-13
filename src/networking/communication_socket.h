#pragma once

#include <functional>
// #include <memory>
#include <netdb.h>
#include <sstream>
#include <string>
#include "communication_socket.h"

namespace tcp_socket
{
using std::string;

class CommunicationSocket
{
private:
	int socket_fd;
	sockaddr_storage address;
	bool is_server;

public:
	CommunicationSocket(int socket_fd, sockaddr_storage address, bool is_server);

	void send(const char* message);
	void send(const std::stringstream& message);
	void send(const string& message);

	void on_recieve(std::function<void(char* message, sockaddr_storage address)> callback_function, bool always);
	void on_recieve(std::function<void(std::stringstream& message, sockaddr_storage address)> callback_function, bool always);
	void on_recieve(std::function<void(std::string& message, sockaddr_storage address)> callback_function, bool always);

	~CommunicationSocket();
};
} // namespace tcp_socket
