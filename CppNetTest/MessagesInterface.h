#pragma once
#include <string>
#include <future>

// This class specifies what has to be included in classes that inherit from this one. 
class MessagesInterface {
public:
    virtual ~MessagesInterface() {} // Deconstructor

    // Functions for sending messages.
    virtual std::future<int> SendMSG(std::string message) = 0;
    virtual std::future<int>SendMSG(std::string message, short timesToTrySendingMessage) = 0;

    //  Function for receiving messages.
    virtual std::future<int> ListenForMessage() = 0;
};