#pragma once
#include <iostream>
#include "Client.h"

class UI
{
private:
	void ChatBox();
	Client* client = new Client("127.0.0.1", 12345);

public:
	UI();

	void Run();
};
