#pragma once
#include "SocketHandler.h"

class MessageHandler:SocketHandler
{
protected:
	void ListenForMessage();

public:
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