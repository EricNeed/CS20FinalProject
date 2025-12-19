#include<iostream>
#include"client/tick_client.h"
#include"server/tick_server_main.h"

TickClient tick_client;
TickServer tick_server;

int main(){
    std::cout << "The game is starting up..." << std::endl;
        tick_client.tick_client();
        tick_server.ticking();
    return 0;
}