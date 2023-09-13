#pragma once

#include <functional>
// #include <memory>
#include <netdb.h>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
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

	// std::vector<std::thread> recieve_threads;

public:
	CommunicationSocket(int socket_fd, sockaddr_storage address, bool is_server);

	bool operator==(const CommunicationSocket& other_socket);

	void send(const char* message) const;
	void send(std::stringstream& message) const;
	void send(const string& message) const;

	void on_recieve(std::function<void(char* message, const CommunicationSocket& socket)> callback_function);
	void on_recieve(std::function<void(std::stringstream& message, const CommunicationSocket& socket)> callback_function);
	void on_recieve(std::function<void(std::string& message, const CommunicationSocket& socket)> callback_function);

	~CommunicationSocket();
};
} // namespace tcp_socket
