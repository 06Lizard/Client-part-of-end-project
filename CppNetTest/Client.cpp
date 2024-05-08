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

void Client::CloseSocket()
{
    closesocket(clientSocket);
    WSACleanup();
}

// Returns 0 if successfully sent
int Client::SendMSG(std::string message)
{
    if (send(clientSocket, message.c_str(), strlen(message.c_str()), 0) == SOCKET_ERROR)
    {
        std::cerr << "Error sending data: " << WSAGetLastError() << " with the message '" << message << "'" << std::endl;
        return WSAGetLastError();
    }
    else
    {
        std::cout << "Message sent successfully\n" << std::endl;
        return 0;
    }
}

int Client::SendMSG(std::string message, short timesToTrySendingMessage)
{
    // In case the user inputs a negative number or zero
    if (timesToTrySendingMessage < 1)
    {
        timesToTrySendingMessage = 1;
    }

    // Loop x amount of times to try sending the message. Exits the loop once successfully sent. 
    for (short i = 0; i > timesToTrySendingMessage; i++)
    {
        std::cout << "Tried sending message " + i + 1 << " times" << std::endl;
        if (SendMSG(message) == 0)
        {
            break;
            return 0; // Returning 0 means successfully sent
        }
    }
    return 1; // Returning 1 means failed to send
}
