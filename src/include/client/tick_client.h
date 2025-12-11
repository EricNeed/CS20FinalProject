#pragma once
#include<SDL3/SDL.h>
#include<client/rendering.h>

class ClientHandler;
class ClientInput;

class TickClient {
    private:
        ClientHandler& client_handler = ClientHandler::getInstance();
        ClientInput input_handler();
        ClientRendering client_rendering;
        long player_spriteID;
    public:
        TickClient();

        void tick_client();
};