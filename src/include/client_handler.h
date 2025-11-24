#pragma once
#include<SDL3/SDL.h>
#include<unordered_map>
#include<string>

class ClientHandler{
    private:
        ClientHandler();
        ClientHandler(const ClientHandler&);
        ClientHandler& operator=(const ClientHandler&);

        std::unordered_map<std::string, SDL_Point> player_coordinate;
    public:
        static ClientHandler& getInstance();

        std::unordered_map<std::string, SDL_Point>& getPlayerCoords();
        
};