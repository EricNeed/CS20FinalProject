#pragma once
#include "SDL3/SDL.h"

class SpriteManager; // Forward declaration

class ClientRendering{
    private:
        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;
        SpriteManager &sprite_manager = SpriteManager::getOnlyInstance();


    public:
        ClientRendering();
        void tick_render();     
};