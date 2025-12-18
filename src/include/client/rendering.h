#pragma once
#include "SDL3/SDL.h"
#include <unordered_map>

class SpriteManager; // Forward declaration

class ClientRendering{
    private:
        struct TextureProperties{
            SDL_Texture* texture;
            int width;
            int height;
        };
        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;
        SpriteManager &sprite_manager = SpriteManager::getOnlyInstance();
        std::unordered_map<std::string, TextureProperties> texture_map;

    public:
        ClientRendering();
        void tickRender();   
        TextureProperties newTexture(std::string texture_dir);
};