#pragma once
#include <iostream>
#include "Client.h"
#include "SocketHandler.h"

class UI : public SocketHandler
{
private:
	bool running;
	Client* client = new Client("127.0.0.1", 12345);
	void ChatBox();
	void LogIn();

public:
	UI();
	void Run();

};
