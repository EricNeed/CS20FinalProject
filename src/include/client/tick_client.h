#pragma once
#include<SDL3/SDL.h>
#include<client/rendering.h>

class ClientHandler;
class ClientInput;

class TickClient {
    private:
        ClientHandler& client_handler;
        long spriteID;
        ClientInput *input_handler;
        ClientRendering client_rendering;
        long player_spriteID;
        
        SDL_Event sdl_event;

        bool game_running = true;
        void processSDLEvents(SDL_Event& sdl_event);
    public:
        TickClient();

        void tick_client();
};