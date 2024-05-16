#include "UI.h"

void UI::ChatBox()
{
	std::string message;
	system("cls");
	std::cout << "- - - - - - CHAT - - - - - -" << "\n" << std::endl;
	while (true)
	{
		client->ListenForMessage();
		std::cin >> message;
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
