#pragma once
#include "SocketHandler.h"

int SocketHandler::ConnectToServer(std::string server_ip, short port)
{
    // Returning 1 or WSAGetLastError is error, 0 is not error.
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        PrintError("WSASttartup failed.");
        return 1;
    }
    else
    {
        PrintSuccessful("WSAStartup succeeded.");
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        PrintError("Error creating socket: " + std::to_string(WSAGetLastError()));
        WSACleanup();
        return WSAGetLastError();
    }
    else
    {
        PrintSuccessful("Creating socket succeded.");
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port); // Use the same port as the server

    // Converting the server_ip string to wide string, and then to wide char pointer
    std::wstring widestr = std::wstring(server_ip.begin(), server_ip.end());
    if (InetPton(AF_INET, widestr.c_str(), &serverAddr.sin_addr) != 1) // Convert IP address from string to binary form
    {
        PrintError("Invalid IP address.");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    else
    {
        PrintSuccessful("Valid IP address.");
    }

    if (connect(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
    {
        PrintError("Error connecting to server: " + std::to_string(WSAGetLastError()));
        closesocket(serverSocket);
        WSACleanup();
        return WSAGetLastError();
    }
    else
    {
        PrintSuccessful("Successfully connected to server.");
    }

    return 0;
}

void SocketHandler::CloseSocket()
{
    closesocket(serverSocket);
    WSACleanup();
}

// Should work but doesn't for whatever reason. Don't use. 
void SocketHandler::Reconnect(std::string server_ip, short port)
{
    CloseSocket();
    WSACleanup();
    ConnectToServer(server_ip, port);
}
