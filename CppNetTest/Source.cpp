#pragma once
#include <iostream>
#include <string>
#include "Client.h"
#include "UI.h"


//#pragma comment(lib, "ws2_32.lib")


std::string typeMSG();
void signup(Client* client, std::string usern, std::string pas);
void login(Client* client, std::string usern, std::string pas);



int main()
{
    Client* testClient = new Client("127.0.0.1", 12345);

    UI* ui = new UI();
    ui->Run();


    //signup(testClient, "walter", "123");
    ////login(testClient, "walter", "123");

    //while (true) {
    //    testClient->ListenForMessage();
    //    testClient->SendMSG(typeMSG());
    //}
}

std::string typeMSG() {
    std::string msg;
    std::cin >> msg;
    return msg;
}

void signup(Client* client, std::string usern, std::string pas) {
    client->ListenForMessage();
    client->SendMSG("signup");
    client->ListenForMessage();
    client->SendMSG("usern");
    client->ListenForMessage();
    client->SendMSG("pas");
    client->ListenForMessage();
    client->SendMSG("pas");
    client->ListenForMessage();
}

void login(Client* client, std::string usern, std::string pas) {
    client->ListenForMessage();
    client->SendMSG("login");
    client->ListenForMessage();
    client->SendMSG("usern");
    client->ListenForMessage();
    client->SendMSG("pas");
    client->ListenForMessage();
}