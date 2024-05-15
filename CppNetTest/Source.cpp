#include <iostream>
#include <string>
#include "Client.h"

//#pragma comment(lib, "ws2_32.lib")

int main() 
{
	std::string message = "balls";

	Client* testClient = new Client("127.0.0.1", 12345);
	
	testClient->SendMSG(message, 3);
	testClient->CloseSocket();
	Sleep(10000000);
}
