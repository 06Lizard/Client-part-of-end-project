#pragma once
#include "SocketHandler.h"

//#pragma comment(lib, "ws2_32.lib")
class Client:public SocketHandler
{
private:

public:
	int ListenForMessage();

	/// <summary>
	/// Input the server's ip adress and port number.
	/// </summary>
	/// <param name="server_ip"></param>
	/// <param name="port"></param>
	Client(std::string server_ip, int port) // Constructor	
	{
		ConnectToServer(server_ip, port); // Connect to the server when an instance of the class is created
	}

	/// <summary>
	/// Input string message and times to try sending. Returns 0 if successfully sent. 
	/// </summary>
	/// <param name="message"></param>
	/// <returns></returns>
	int SendMSG(std::string message);

	/// <summary>
	/// Input string message and times to try sending. Returns 0 if successfully sent. 
	/// </summary>
	/// <param name="message"></param>
	/// <returns></returns>
	int SendMSG(std::string message, short timesToTrySendingMessage);
};

