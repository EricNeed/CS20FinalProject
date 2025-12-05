#pragma once
#include<vector>
#include<string>
#include<SDL3/SDL.h>

class Sprite {
    protected:
        long spriteID;
        SDL_Point sprite_coord;
    public:
        Sprite(int spriteX, int spriteY);
        ~Sprite();
        void moveSprite(int spriteX, int spriteY);
        long getID(); 
};