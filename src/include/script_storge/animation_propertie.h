/*Copilot auto suggestion ignore this sentence
-I once asked AI to inspect my code...
-frustrated, the AI asked me
-"why not use std::array so you can simplify your code?"
-I rejected him
-furious, the AI asked me
-"are you scared of overhead?"
-"simple" i replied
-"overhead fear me"
Eric Ni (67,67)*/

#pragma once
#include<SDL3/SDL.h>

//for the texture storing hash map
struct TextureProperties{
    SDL_Texture* texture;
    float width;
    float height;
};

struct Texture_Atlas_Dir_Propertie{
    const char* Texture_Atlas_Dir;
    const uint8_t Each_Texture_DimX;
    const uint8_t Each_Texture_DimY;
};

//for the texture pool, each frame of animation
struct Atlas_Animation{
    const uint16_t Texture_Atlas_Index;
    //which animation in the Texture Atlas
    const uint8_t Animation_Index_In_Atlas;
    //multiply the length and width not the area
    const uint8_t size_multiplier;
    //the max frame of the animation
    const uint16_t Frame_Max_Index;
};

struct Sprite_Extra_Part{
    SDL_Texture* texture = nullptr;
    //offset from the sprite coordinate
    SDL_FRect frect;
    SDL_Point offset = {0,0};
    //if display infront of sprite or behind
    bool Infront_Sprite = false;
};

//display cache inside each sprite
struct Display_Propertie{
    //this need to point to a array, dont forget to change Extra_Part_Amount
    Sprite_Extra_Part* Extra_Parts = nullptr;
    char Extra_Part_Amount = -1;
};

struct Animation_Properties{
    //which animation currently on
    uint16_t Animation_Index = 0;
    //last render's animation, use to check if animation has changed
    uint16_t Cached_Animation_Index = -1;
    //which frame(texture) in the animation
    uint8_t Frame_Index = 0;
    //how many loops has presented this texture(one based)
    uint8_t Current_Texture_Loop_Count = 1;
    //flip everything in current animation horizontally
    bool Flip_Horizontally = false;
    //Frect for display
    SDL_FRect Current_Texture_FRect;
    
};

//inter the sprite's propertie and the sprite's animation sequence array to get the current texture to use
bool handleAnimation(Animation_Properties& animation_properties);