#pragma once
#include <iostream>
#include <string>
#include "Client.h"
#include "UI.h"


//#pragma comment(lib, "ws2_32.lib")


std::string typeMSG();
int main() 
{
	//std::string message = "balls";

	Client* testClient = new Client("127.0.0.1", 12345);

	while (true) {
		testClient->ListenForMessage();
		//Sleep(5000);
		testClient->SendMSG(typeMSG());
	}


	//UI* ui = new UI();
	//ui->Run();

	//Sleep(10000000);
}

std::string typeMSG() {
	std::string msg;
	std::cin >> msg;
	return msg;
}