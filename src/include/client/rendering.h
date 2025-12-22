#pragma once
#include "SDL3/SDL.h"
#include <unordered_map>
#include<string>

class SpriteManager; // Forward declaration



class ClientRendering{
    private:
        struct TextureProperties{
            SDL_Texture* texture;
            float width;
            float height;
        };

        TextureProperties sprite_profiles[];


        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;
        SpriteManager &sprite_manager;
        std::unordered_map<std::string, TextureProperties> texture_map;

    public:
        ClientRendering();
        void tickRender();
        auto newTexture(std::string texture_dir) -> TextureProperties;
};