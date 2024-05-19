#pragma once
#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h> // Necessary header for InetPton.
#include <string>
#include "Colors.h"

class SocketHandler: public Colors
{
protected:
	SOCKET serverSocket;

	/// <summary>
	/// Connects to the server, need the server's IP address and port number. 
	/// </summary>
	/// <param name="server_ip"></param>
	/// <param name="port"></param>
	/// <returns></returns>
	int ConnectToServer(std::string server_ip, short port);

public:
	/// <summary>
	/// Closes the socket.
	/// </summary>
	void CloseSocket();

	/// <summary>
	/// Reconnects to the server.
	/// </summary>
	void Reconnect(std::string server_ip, short port);
};
