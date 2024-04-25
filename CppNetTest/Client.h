#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h> // Include the necessary header for InetPton
#include <string>

//#pragma comment(lib, "ws2_32.lib")
class Client
{
private:
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	int ConnectToServer(std::string server_ip, int port);

public:
	/// <summary>
	/// Input the server's ip adress and port number.
	/// </summary>
	/// <param name="server_ip"></param>
	/// <param name="port"></param>
	Client(std::string server_ip, int port) // Constructor	
	{
		ConnectToServer(server_ip, port); // Connect to the server when an instance of the class is created
	}
	
	/// <summary>
	/// Input string message. Returns 0 if successfully sent. 
	/// </summary>
	/// <param name="message"></param>
	/// <returns></returns>
	int SendMSG(std::string message);
};

