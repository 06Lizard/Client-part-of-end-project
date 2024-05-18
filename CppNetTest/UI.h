#pragma once
#include <iostream>
#include "Client.h"
#include "Colors.h"

class UI : public Colors
{
private:
	bool running;

	void ChatBox();
	Client* client = new Client("127.0.0.1", 12345);

public:
	UI();
	void Run();

};
