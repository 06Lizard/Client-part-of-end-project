#include "Client.h"

// Returning 1 or WSAGetLastError is error, 0 is not error.
int Client::ConnectToServer(std::string server_ip, int port)
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
    {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "WSAStartup succeeded" << std::endl;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) 
    {
        std::cerr << "Error creating socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return WSAGetLastError();
    }
    else
    {
        std::cout << "Creating socket succeeded" << std::endl;
    }
    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port); // Use the same port as the server

    // Converting the server_ip string to wide string, and then to wide char pointer
    std::wstring widestr = std::wstring(server_ip.begin(), server_ip.end());
    if (InetPton(AF_INET, widestr.c_str(), &serverAddr.sin_addr) != 1) // Convert IP address from string to binary form
    {
        std::cerr << "Invalid IP address\n" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    else
    {
        std::cout << "Valid ip adress" << std::endl;
    }

    if (connect(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) 
    {
        std::cerr << "Error connecting to server: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return WSAGetLastError();
    }
    else
    {
        std::cout << "Connected to server" << std::endl;

        // Start listening to new detached thread
        std::thread listenThread(&Client::ListenForMessage, this);
        listenThread.detach();
    }
    
    return 0;
}

//std::thread Client::listeningThread(SOCKET serverSocket)
//{
//    Client client("127.0.0.1", 12345);
//    client.ListenForMessage();
//
//}

void Client::CloseSocket()
{
    closesocket(serverSocket);
    WSACleanup();
}

// Returns 0 if successfully sent
int Client::SendMSG(std::string message)
{
    if (send(serverSocket, message.c_str(), strlen(message.c_str()), 0) == SOCKET_ERROR)
    {
        std::cerr << "Error sending data: " << WSAGetLastError() << " with the message '" << message << "'" << std::endl;
        return WSAGetLastError();
    }
    else
    {
        std::cout << "Message sent successfully" << std::endl;
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
    for (short i = 0; i < timesToTrySendingMessage; i++)
    {
        std::cout << "Tried sending message " << i + 1 << " times" << std::endl;
        if (SendMSG(message) == 0)
        {
            break;
            return 0; // Returning 0 means successfully sent
        }
    }
    return 1; // Returning 1 means failed to send
}

void Client::ListenForMessage()
{
    char buffer[1024]; // Buffer to store incoming messages
    int bytesReceived;

    while (true) // Loops to keep listening
    {
        bytesReceived = recv(serverSocket, buffer, sizeof(buffer) - 1, 0);

        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0';
            std::cout << "Message received from server: " << buffer << std::endl;
        }
        //std::cout << "waiting for message" << std::endl;
        //else if (bytesReceived == 0)
        //{
        //    std::cout << "Lost connection to server." << std::endl;
        //    break; // Exit the loop if the connection is closed
        //}
        //else
        //{
        //    std::cerr << "Error receiving data: " << WSAGetLastError() << std::endl;
        //    break;
        //}
        //Sleep(333);
    }

    // Clean up resources after exiting the loop
    CloseSocket();
}