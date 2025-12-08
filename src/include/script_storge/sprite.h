#pragma once
#include<vector>
#include<string>
#include<SDL3/SDL.h>
#include<server/sprite_manager.h>

enum class SpriteType{
    Player,
};

class Sprite {
    protected:
        long spriteID;
        SDL_Point sprite_coord;
        SpriteType sprite_type;

        SpriteManager& spriter_manager = SpriteManager::getOnlyInstance();
    public:
        Sprite(long ID);
        ~Sprite();
        void moveSprite(int spriteX, int spriteY);
        long getID(); 
        SpriteType getType();
        virtual void logTypeToSpriteManager();
};