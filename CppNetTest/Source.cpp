#include <iostream>
#include <winsock2.h>
#include <Ws2tcpip.h> // Include the necessary header for InetPton

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Use the same port as the server

    // Convert IP address from string to binary form
    if (InetPton(AF_INET, TEXT("192.168.68.81"), &serverAddr.sin_addr) != 1) {
        std::cerr << "Invalid IP address\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server: " << WSAGetLastError() << "\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    const char* message = "Hello world";
    if (send(clientSocket, message, strlen(message), 0) == SOCKET_ERROR) {
        std::cerr << "Error sending data: " << WSAGetLastError() << "\n";
    }
    else {
        std::cout << "Message sent successfully\n";
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
