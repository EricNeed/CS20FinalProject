#pragma once
#include<vector>
#include<string>
#include<SDL3/SDL.h>

class Sprite {
    private:
        static std::vector<Sprite*> sprite_list;
        long spriteID;
        SDL_Point sprite_coord;
    public:
        Sprite(int spriteX, int spriteY);
        void moveSprite(int spriteX, int spriteY);
        int skibidi;
        long getID(); 
};