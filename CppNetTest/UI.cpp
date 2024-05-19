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
		client->ListenForMessage();
		std::getline(std::cin, message);
		client->SendMSG(message);
	}
}

void UI::LogIn()
{
	short messageListenReturn;
	running = true;
	system("cls"); // Clear console
	std::string message;
	SetColor(0, 7);
	std::cout << "- - - - - - Log In / Sign Up - - - - - -" << "\n" << std::endl;
	ResetColor();

	while (running)
	{
		messageListenReturn = client->ListenForMessage().get();
		switch (messageListenReturn)
		{
		case 2:
			ChatBox();
			break;

		case 3:
			PrintWarning("[Press any key to attempt reconnecting.]");
			std::cin.get();
			Reconnect("127.0.0.1", 12345); // Doesn't work, unable to retrieve data after successfully reconnecting. 
			break;
			
		default:
			break;
		}

		std::getline(std::cin, message);
		client->SendMSG(message);
	}
}

UI::UI()
{

}

void UI::Run()
{
	Sleep(3000);
	LogIn();
	//ChatBox();
}
