#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h> // Include the necessary header for InetPton
#include <string>

//#pragma comment(lib, "ws2_32.lib")
class Send
{
private:
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bool ConnectToServer(std::string server_ip, int port);

public:
	Send(std::string server_ip, int port) // Constructor	
	{
		ConnectToServer(server_ip, port); // Connect to the server when an instance of the class is created
	}
	
	bool SendMSG(std::string message);
};

