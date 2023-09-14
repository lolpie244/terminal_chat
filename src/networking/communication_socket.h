#pragma once

#include <functional>
// #include <memory>
#include <netdb.h>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include "communication_socket.h"
#include "file_descriptor.h"

namespace tcp_socket
{
using std::string;

class CommunicationSocket
{
private:
	FileDescriptor socket_fd;
	sockaddr_storage address;
	bool is_server;

	// std::vector<std::thread> recieve_threads;

public:
	CommunicationSocket(FileDescriptor socket_fd, sockaddr_storage address, bool is_server);

	bool operator==(const CommunicationSocket& other_socket);

	void close_connection() const;

	void send(const char* message) const;
	void send(std::stringstream& message) const;
	void send(const string& message) const;

	bool on_recieve(std::function<void(char* message, const CommunicationSocket& socket)> callback_function);
	bool on_recieve(std::function<void(std::stringstream& message, const CommunicationSocket& socket)> callback_function);
	bool on_recieve(std::function<void(std::string& message, const CommunicationSocket& socket)> callback_function);

	~CommunicationSocket();
};
} // namespace tcp_socket
