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
    SDL_Point Coord;
    int WalkSpeed;
    std::vector<std::string> Textures;
    unsigned char Current_Texture_Index = 0;
};

class Sprite {
    private:
        //needed in each sprite
        Properties_Base sprite_properties;
    protected:
        SpriteManager& sprite_manager = SpriteManager::getOnlyInstance();
        virtual void logTypeToSpriteManager() = 0;
    public:
        
        //needed to be overided if have special struct
        virtual const Properties_Base* getProperties();

        Sprite(long ID);
        ~Sprite();
        void moveSprite(SDL_Point new_coord);
};