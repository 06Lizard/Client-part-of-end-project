#pragma once
#include "SocketHandler.h"
#include <future>
#include "MessagesInterface.h"
// Gets colors from SocketHandler.h.

class Client : public SocketHandler, public MessagesInterface
{
public:
	/// <summary>
	/// Awaits incoming messages. 
	/// </summary>
	/// <returns></returns>
	std::future<int> ListenForMessage();

	/// <summary>
	/// Input the server's ip address and port number.
	/// </summary>
	/// <param name="server_ip"></param>
	/// <param name="port"></param>
	Client(std::string server_ip, int port) // Constructor	
	{
		ConnectToServer(server_ip, port); // Connect to the server when an instance of the class is created.
	}

	/// <summary>
	/// Input string message and times to try sending. Returns 0 if successfully sent. 
	/// </summary>
	/// <param name="message"></param>
	/// <returns></returns>
	std::future<int> SendMSG(std::string message);

	/// <summary>
	/// Input string message and times to try sending. Returns 0 if successfully sent. 
	/// </summary>
	/// <param name="message"></param>
	/// <returns></returns>
	std::future<int> SendMSG(std::string message, short timesToTrySendingMessage);
};