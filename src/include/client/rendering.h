#pragma once
#include"SDL3/SDL.h"
#include<unordered_map>
#include<string>

class SpriteManager; // Forward declaration



class ClientRendering{
    private:
        struct TextureProperties{
            SDL_Texture* texture;
            float width;
            float height;
        };


        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;
        SpriteManager &sprite_manager;
        std::unordered_map<const char*, TextureProperties> texture_map;
        

    public:
        ClientRendering();
        void tickRender();
        auto newTexture(const char* texture_dir) -> TextureProperties*;
        void fullScreenToggle(bool enable_fullscreen);
};