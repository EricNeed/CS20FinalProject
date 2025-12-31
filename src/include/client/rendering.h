#pragma once
#include"SDL3/SDL.h"
#include<unordered_map>
#include<string>
#include"script_storge/texture_pool.h"

class SpriteManager; // Forward declaration



class ClientRendering{
    private:
        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;
        SpriteManager &sprite_manager;
        std::unordered_map<const char*, TextureProperties> texture_map;
        
        Display_Propertie display_order_sorter[720];
    public:
        ClientRendering();
        void tickRender();
        void newTexture(const char* texture_dir);
        auto getTexture(const char* texture_dir) -> TextureProperties*;
        void fullScreenToggle(bool enable_fullscreen);
};