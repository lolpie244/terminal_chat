#pragma once

#include <functional>
#include <memory>
#include <netdb.h>
#include <string>
#include "communication_socket.h"

namespace tcp_socket
{
using std::string;

class ConnectionSocket
{
	private:
	int socket_fd;
	addrinfo *address;
	bool is_binded = false;
public:
	ConnectionSocket(const char *host, const char *port, const addrinfo &address);
	ConnectionSocket(const char *port);

	void bind();
	CommunicationSocket connect();
	void listen(std::function<void(CommunicationSocket communication_socket)> after_accept, int queue_size=20);

	~ConnectionSocket();

};
}
