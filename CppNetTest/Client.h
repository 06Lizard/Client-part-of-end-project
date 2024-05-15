#pragma once
#include "SocketHandler.h"
#include "MessageHandler.h"

//#pragma comment(lib, "ws2_32.lib")
class Client:public SocketHandler, public MessageHandler
{
public:
	/// <summary>
	/// Input the server's ip adress and port number.
	/// </summary>
	/// <param name="server_ip"></param>
	/// <param name="port"></param>
	Client(std::string server_ip, int port) // Constructor	
	{
		SocketHandler::ConnectToServer(server_ip, port); // Connect to the server when an instance of the class is created
	}
};

