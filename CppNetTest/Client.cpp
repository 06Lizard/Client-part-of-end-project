#pragma once
#include "Client.h" 

// Returns 0 if successfully sent.
std::future<int> Client::SendMSG(std::string message)
{
    // Start a new async task so it doesn't need to wait for it to finish before doing ohter stuff.
    return std::async(std::launch::async, [this, message]() -> int
    {
        // If statement that checks if the send function returns a socket error (failed).
        if (send(serverSocket, message.c_str(), message.size(), 0) == SOCKET_ERROR)
        {
            // If sending fails, it prints an error message
            PrintError("Error sending data: " + std::to_string(WSAGetLastError()) + ", with the message '" + message + "'.");
            return WSAGetLastError();
        }
        else
        {
            //PrintSuccessful("Message sent successfully.");
            return 0;
        }
    });
}

std::future<int> Client::SendMSG(std::string message, short timesToTrySendingMessage)
{
    return std::async(std::launch::async, [this, message, timesToTrySendingMessage]() -> int 
    {
        // In case the user inputs a negative number or zero.
        short attempts = (timesToTrySendingMessage < 1) ? 1 : timesToTrySendingMessage;

        // Loop x amount of times to try sending the message. Exits the loop once successfully sent.
        for (short i = 0; i < attempts; i++)
        {
            if (SendMSG(message).get() == 0)
            {
                break;
                return 0; // Returning 0 means successfully sent.
            }
        }
        return 1; // Returning 1 means failed to send.
    });
}

//Returns 0 if it got a message, and returns 2 if the message is that the user has logged in, 3 if lost connection to the server. 
std::future<int> Client::ListenForMessage()
{
    // Using async so that the program can do many things at the same time, it no longer has to wait for a process to finish before starting another. Reduces delay and makes the program more responsive. 
    return std::async(std::launch::async, [this]() -> int
    {
        char buffer[1024]; // Buffer to store incoming messages.
        int bytesReceived; // Stores how much data has been received to see if there is a connection. 

        bytesReceived = recv(serverSocket, buffer, sizeof(buffer) - 1, 0);

        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0'; // Null terminator at the bytesReceived' byte in buffer array. Used by the program to know where the end of the message is. 
            std::string messageString(buffer); // Convert char buffer into a string.

            size_t delimiterPos = messageString.find(':'); // Split the message at ':' to color usernames and text differently.
            if (delimiterPos != std::string::npos) 
            {
                // Divides the split string into two different ones for clarity.
                std::string username = messageString.substr(0, delimiterPos);
                std::string messageText = messageString.substr(delimiterPos + 1);

                // Make the username and arrows different colors, then reset to default color and print the text.
                SetColor(3);
                std::cout << username;
                SetColor(12);
                std::cout << " >> ";
                ResetColor();
                std::cout << messageText << std::endl;
            }
            else // If a colon wasn't found, it is a message from the server. Then manually add "Server >>" with the right colors. 
            {
                // Make the username one color, then reset to default color and print the text.
                SetColor(3);
                std::cout << "Server";
                SetColor(12);
                std::cout << " >> ";
                ResetColor();
                std::cout << messageString << std::endl;
            }

            /*
            Checking if the user has logged in or signed up by checking if the message contains things that hint at the user having successfully logged in or signed up. Not a secure or reliable solution, but I didn't have any other options
            because there is currently no other way of detecting a login or sign up from the server. Will work on a better solution if I have time.
            */
            if (messageString.find("Login successful") != std::string::npos)
            {
                if (!(messageString.find(":") != std::string::npos)) // The login successful message doesn't contain a ':' because it's not from another user, so it checks for that.
                {
                    Sleep(3000);
                    return 2; // Returns 2, indicating that login has succeeded.
                }
            }
            if (messageString.find("Signup successful") != std::string::npos)
            {
                if (!(messageString.find(":") != std::string::npos))
                {
                    Sleep(3000);
                    return 3; // Returns 3, indicating that the sign up has succeeded.
                }
            }
            return 0;
        }
        else if (bytesReceived == 0)
        {
            // No connection if there is no data.
            PrintWarning("Lost connection to server.");
            return 1;
        }
        else
        {
            // If the recieved bytes is negative, something has gone wrong.
            PrintError("Error receiving listening data: " + std::to_string(WSAGetLastError()));
            return 1;
        }
    });
}
