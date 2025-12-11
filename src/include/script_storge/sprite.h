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
        SpriteType sprite_type;
        SDL_Point sprite_coord;
        int walk_speed;

        SpriteManager& spriter_manager = SpriteManager::getOnlyInstance();
        virtual void logTypeToSpriteManager() = 0;
    public:
        const long getID() const; 
        const SpriteType getType() const;
        const SDL_Point getCoord() const;
        const int getSpeed() const;

        Sprite(long ID);
        ~Sprite();
        void moveSprite(SDL_Point new_coord);
};