#pragma once
#include "SocketHandler.h"

int SocketHandler::ConnectToServer(std::string server_ip, int port)
{
    // Returning 1 or WSAGetLastError is error, 0 is not error.
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
    }

    return 0;
}

void SocketHandler::CloseSocket()
{
    closesocket(serverSocket);
    WSACleanup();
}