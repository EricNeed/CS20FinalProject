#pragma once
#include<SDL3/SDL.h>
#include<src/include/script_storge/player.h>
#include<src/include/server/client_handler.h>
#include<server/client_handler.h>
#include<server/sprite_manager.h>

class ClientInput{
    private:
        const bool *keyboard_states;
        uint16_t playerID = 0;
        SpriteManager& sprite_manager = SpriteManager::getOnlyInstance();
        ClientHandler& client_handler = ClientHandler::getInstance();
    public:
        ClientInput(uint16_t ID);

        void processUserInput();
};