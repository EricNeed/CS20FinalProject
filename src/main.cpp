#include<iostream>
#include"client/tick_client.h"
#include"server/tick_server_main.h"


int main(){
    std::cout << "The game is starting up..." << std::endl;

    TickClient tick_client;
    std::cout << "after TickClient \n";
    TickServer tick_server;
    
    tick_client.tick_client();
    tick_server.ticking();

    while(true){}
    return 0;
}