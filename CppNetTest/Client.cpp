#include "Client.h"

// Returning 1 or WSAGetLastError is error, 0 is not error.
int Client::ConnectToServer(std::string server_ip, int port)
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
    {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    if (clientSocket == INVALID_SOCKET) 
    {
        std::cerr << "Error creating socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return WSAGetLastError();
    }
    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port); // Use the same port as the server

    // Converting the server_ip string to wide string, and then to wide char pointer
    std::wstring widestr = std::wstring(server_ip.begin(), server_ip.end());
    if (InetPton(AF_INET, widestr.c_str(), &serverAddr.sin_addr) != 1) // Convert IP address from string to binary form
    {
        std::cerr << "Invalid IP address\n" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) 
    {
        std::cerr << "Error connecting to server: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return WSAGetLastError();
    }
    else
    {
        std::cout << "Connected to server" << std::endl;
    }
    return 0;
}

int Client::SendMSG(std::string message, short timesToTrySendingMessage)
{
    for (short i = 0; i > timesToTrySendingMessage; i++)
    {
        std::cout << "Tried sending message " + i + 1 << std::endl;
        if (send(clientSocket, message.c_str(), strlen(message.c_str()), 0) == SOCKET_ERROR)
        {
            std::cerr << "Error sending data: " << WSAGetLastError() << " with the message '" << message << "'" << std::endl;
            return WSAGetLastError();
        }
        else
        {
            std::cout << "Message sent successfully\n" << std::endl;
            break; // Break out of loop if successfully sent
        }
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}
