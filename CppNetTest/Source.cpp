#include <iostream>
#include <string>
#include "Send.h"

//#pragma comment(lib, "ws2_32.lib")

int main() 
{
	std::string message;
	std::cin >> message;

	Send* test = new Send("192.168.174.63", 12345);
	test->SendMSG(message);
}
