#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h> // Include the necessary header for InetPton
#include <string>
#include <thread>

//#pragma comment(lib, "ws2_32.lib")
class Client
{
private:
	SOCKET serverSocket;
	int ConnectToServer(std::string server_ip, int port);
	void ListenForMessage();

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
	/// Closes the socket
	/// </summary>
	void CloseSocket();

	/// <summary>
	/// Input string message and times to try sending. Returns 0 if successfully sent. 
	/// </summary>
	/// <param name="message"></param>
	/// <returns></returns>
	int SendMSG(std::string message);
	
	/// <summary>
	/// Input string message and times to try sending. Returns 0 if successfully sent. 
	/// </summary>
	/// <param name="message"></param>
	/// <returns></returns>
	int SendMSG(std::string message, short timesToTrySendingMessage);
};

