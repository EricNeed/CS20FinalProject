#pragma once
#include<SDL3/SDL.h>
#include<unordered_map>
#include<string>
#include<server/sprite_manager.h>
#include<memory>
#include<script_storge/player.h>

class ClientHandler{
    private:
        ClientHandler(){}
        ClientHandler(const ClientHandler&) = delete;
        ClientHandler& operator=(const ClientHandler&) = delete;
        SpriteManager& sprite_manager = SpriteManager::getOnlyInstance();
    public:
        static ClientHandler& getInstance();
        void processClientRequest();
        void newPlayerCoord(long player_spriteID, SDL_Point new_coord);
        long newConnectedClient();
};

class ClientSync{
    public:
        void syncCoord();
        void newSprite();
};