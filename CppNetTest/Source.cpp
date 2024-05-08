#include <iostream>
#include <string>
#include "Client.h"

//#pragma comment(lib, "ws2_32.lib")

int main() 
{
	std::string message = "balls";

	Client* testClient = new Client("192.168.174.63", 12345);
	
	testClient->SendMSG(message, 3);
}
