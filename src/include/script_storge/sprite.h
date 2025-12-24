#pragma once
#include<vector>
#include<string>
#include<SDL3/SDL.h>
#include<server/sprite_manager.h>


enum class SpriteType{
    Player,
};

struct Properties_Base{
    long ID;
    SpriteType Type;
    SDL_Point Coord = {0,0};
    int WalkSpeed;
    int Texture_Collection_Index;
    unsigned char Current_Texture_Index = 0;
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
        
        virtual void moveSprite(SDL_Point new_coord);

        virtual const Properties_Base* getSpecialProperties() = 0;

        // ~Sprite();
};