#pragma once
#include<SDL3/SDL.h>
#include<client/rendering.h>

class ClientHandler;
class ClientInput;

class TickClient {
    private:
        ClientHandler& client_handler;
        long spriteID;
        ClientInput* input_handler = nullptr;
        ClientRendering client_rendering;
        long player_spriteID;
        
        void processSDLEvents(SDL_Event& sdl_event);
    public:
        TickClient();
        void tick_client();
        ~TickClient();
        void toggleFullScreen(bool enable_fullscreen){client_rendering.fullScreenToggle(enable_fullscreen);}
};