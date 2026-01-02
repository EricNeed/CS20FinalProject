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
        uint16_t playerID;

        static constexpr uint16_t order_sorter_max = 720;
        Animation_Properties* display_order_sorter[order_sorter_max];
        int window_width, window_height, map_screen_cornerX, map_screen_cornerY, player_map_coordX, player_map_coordY;

        //please use the left top corner, margin only for left and top
        bool pointNotOnScreen(const int pointX, const int pointY, const uint8_t margin){return (pointX < -margin || pointY < -margin || pointX > window_width || pointY > window_height);};

        void placeInDisplayOrderArray(int y_max, Animation_Properties*);
    public:
        ClientRendering(uint16_t ID);
        void tickRender();
        void newTexture(const char* texture_dir);
        auto getTexture(const char* texture_dir) -> TextureProperties*;
        void fullScreenToggle(bool enable_fullscreen);
};