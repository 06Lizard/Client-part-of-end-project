#include "UI.h"

void UI::ChatBox()
{
	running = true;
	std::string message;
	system("cls");
	std::cout << "- - - - - - CHAT - - - - - -" << "\n" << std::endl;
	while (running)
	{
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

std::future<int> UI::Recive() 
{
	return std::async(std::launch::async, [this]() -> int {
		while (running)
			client->ListenForMessage();
		return 0;
	});
}