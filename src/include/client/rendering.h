#pragma once
#include"SDL3/SDL.h"
#include<unordered_map>
#include<string>
#include"script_storge/texture_pool.h"

class SpriteManager; // Forward declaration
struct Properties_Base;


class ClientRendering{
    private:
        ClientRendering();
        ClientRendering(const ClientRendering&) = delete;
        ClientRendering& operator=(const ClientRendering&) = delete;
        //is_first_call should always leave false unless the first time call this function

        SDL_Window *sdl_window;
        SDL_Renderer *sdl_renderer;
        SpriteManager &sprite_manager;
        static constexpr uint16_t TEXTURE_MAP_MAX = 2000;
        SDL_Texture** texture_map;
        uint16_t playerID;

        static constexpr uint16_t order_sorter_max = 720;
        Properties_Base** display_order_sorter;
        int window_width, window_height, map_screen_cornerX, map_screen_cornerY;
        //cursor's position on map
        float cursorX, cursorY;
        static SDL_FRect part_dstrect;

        //please use the left top corner, margin only for left and top
        bool pointNotOnScreen(const int pointX, const int pointY, const uint8_t margin){return (pointX < -margin || pointY < -margin || pointX > window_width || pointY > window_height);};

        void placeInDisplayOrderArray(int y_max, Properties_Base*);
        void renderSpriteParts(Properties_Base* player_properties, bool infront);
        void renderSprite();
        void renderCursor();
        void renderFloorTiles();

        //no rotation, dstrect can have w and h left empty/unchanged
        
        void renderDrawSimple(Atlas_Animation animation, SDL_FRect& dstrect, uint8_t frame_index);
        void renderDrawRotated();
    public:
        static ClientRendering& getOnlyInstance(uint16_t ID, bool is_first_call = false);
        void tickRender();
        void newTexture(uint16_t texture_dir_index);
        SDL_Texture* getTexture(uint16_t texture_dir_index);
        void fullScreenToggle(bool enable_fullscreen);
};