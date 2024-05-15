#pragma once
#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h> // Include the necessary header for InetPton
#include <string>
#include <thread>

class SocketHandler
{
protected:
	SOCKET serverSocket;
	int ConnectToServer(std::string server_ip, int port);

public:
	/// <summary>
	/// Closes the socket
	/// </summary>
	void CloseSocket();
};
