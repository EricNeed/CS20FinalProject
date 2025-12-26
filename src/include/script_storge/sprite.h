#pragma once
#include<vector>
#include<string>
#include<SDL3/SDL.h>
#include<server/sprite_manager.h>
#include<script_storge/animation_propertie.h>

enum class SpriteType{
    Player,
};

struct Properties_Base{
    long ID;
    SpriteType Type;
    SDL_Point Coord = {0,0};
    int WalkSpeed;
    Animation_Properties Animation;
};

class Sprite {
    private:
        //use the getProperties() so can use derived struct in base class
        Properties_Base* derived_properties;
    protected:
        SpriteManager& sprite_manager = SpriteManager::getOnlyInstance();
        virtual void logTypeToSpriteManager();

    public:
        
        //needed to be overided if have special struct
        virtual const Properties_Base* getProperties() = 0;
        Sprite(long ID, Properties_Base* properties_ptr);
        
        void moveSprite(SDL_Point new_coord);
        // ~Sprite();
};