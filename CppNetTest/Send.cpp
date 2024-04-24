#include "Send.h"

bool Send::ConnectToServer(std::string server_ip, int port)
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return false;
    }

    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return false;
    }
    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port); // Use the same port as the server

    // Converting the server_ip string to wide string, and then to wide char pointer
    std::wstring widestr = std::wstring(server_ip.begin(), server_ip.end());
    if (InetPton(AF_INET, widestr.c_str(), &serverAddr.sin_addr) != 1) // Convert IP address from string to binary form
    {
        std::cerr << "Invalid IP address\n";
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server: " << WSAGetLastError() << "\n";
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }
    else
    {
        std::cout << "Connected to server" << std::endl;
    }
    return false;
}

bool Send::SendMSG(std::string message)
{
    if (send(clientSocket, message.c_str(), strlen(message.c_str()), 0) == SOCKET_ERROR)
    {
        std::cerr << "Error sending data: " << WSAGetLastError() << "\n";
        return false;
    }
    else
    {
        std::cout << "Message sent successfully\n";
    }

    std::cout << "Press enter to exit" << std::endl;
    Sleep(1000);
    std::cin.get();

    closesocket(clientSocket);
    WSACleanup();
    return true;
}
