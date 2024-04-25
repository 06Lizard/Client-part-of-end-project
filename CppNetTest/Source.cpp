#include <iostream>
#include <string>
#include "Client.h"

//#pragma comment(lib, "ws2_32.lib")

int main() 
{
	std::string message = "balls";

	Client* testClient = new Client("192.168.174.63", 12345);
	
	// Attempt sending message 3 times, break out of loop if successfully sent
	for (int i = 0; i < 3; i++) 
	{
		std::cout << "Sent message: " << i + 1 << std::endl;
		if (testClient->SendMSG(message) == 0) 
		{
			std::cout << "Successfully sent" << std::endl;
			break;
		}
	}
}
