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

	void send(const char* message) const;
	void send(const std::stringstream& message) const;
	void send(const string& message) const;

	void on_recieve(std::function<void(char* message, const CommunicationSocket& socket)> callback_function, bool always);
	void on_recieve(std::function<void(std::stringstream& message, const CommunicationSocket& socket)> callback_function, bool always);
	void on_recieve(std::function<void(std::string& message, const CommunicationSocket& socket)> callback_function, bool always);

	~CommunicationSocket();
};
} // namespace tcp_socket
