#pragma once
#include <iostream>
#include "Client.h"
#include <future>

class UI
{
private:
	bool running;
	void ChatBox();
	Client* client = new Client("127.0.0.1", 12345);
	std::future<int> Recive();

public:
	UI();

	void Run();
};
