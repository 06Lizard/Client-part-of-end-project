#include "UI.h"

void UI::ChatBox()
{
	running = true;
	std::string message;
	system("cls"); // Clear console
	SetColor(0, 7);
	std::cout << "- - - - - - CHAT - - - - - -" << "\n" << std::endl;
	ResetColor();
	while (running)
	{
		std::cin >> message;
		client->ListenForMessage();
		client->SendMSG(message);
		std::cin.get();
	}
}

UI::UI()
{

}

void UI::Run()
{
	ChatBox();
}
