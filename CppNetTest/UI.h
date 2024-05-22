#pragma once
#include <iostream>
#include "Client.h"
#include "SocketHandler.h"

class UI : public SocketHandler
{
private:
	bool running;
	Client* client = new Client("192.168.115.63", 12345);

	/// <summary>
	/// Brings the user to the chat screen.
	/// </summary>
	void ChatBox();

	/// <summary>
	/// Brings the user to the log in screen.
	/// </summary>
	void LogIn();

public:
	/// <summary>
	/// Start the program.
	/// </summary>
	void Run();
};
