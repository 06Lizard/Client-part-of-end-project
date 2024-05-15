#pragma once
#include "Client.h" 

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

    // Loop x amount of times to try sending the message. Exits the loop once successfully sent
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

//Returns 0 if it got a message
int Client::ListenForMessage()
{
    char buffer[1024]; // Buffer to store incoming messages
    int bytesReceived;

    bytesReceived = recv(serverSocket, buffer, sizeof(buffer) - 1, 0);

    std::cout << "Listening for messages" << std::endl;

    if (bytesReceived > 0)
    {
        buffer[bytesReceived] = '\0';
        std::cout << "Message received from server: " << buffer << std::endl;
        return 0;
    }
    else if (bytesReceived == 0)
    {
        std::cout << "lost connection to server." << std::endl;
        return 1;
    }
    else
    {
        std::cerr << "Error receiving listening data: " << WSAGetLastError() << std::endl;
        return 1;
    }
}