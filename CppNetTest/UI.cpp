#include "UI.h"

void UI::ChatBox()
{
	std::string message;
	system("cls");
	std::cout << "- - - - - - CHAT - - - - - -" << "\n" << std::endl;
	while (true)
	{
		std::cin >> message;
		client->SendMSG(message);
		client->ListenForMessage();
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
