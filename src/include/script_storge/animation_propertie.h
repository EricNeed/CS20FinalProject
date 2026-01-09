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
#include<utility>

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
    const uint16_t Frame_Max;
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

inline bool handleAnimation(Animation_Properties& animation_properties){
    const std::pair<const Atlas_Animation, const uint8_t*>* animation = &Animations[animation_properties.Animation_Index];
}

//inter the sprite's propertie and the sprite's animation sequence array to get the current texture to use
inline std::pair<const Animation_Frame*, bool> handleAnimation2(Animation_Properties& animation_properties, const std::pair <const std::pair<Animation_Frame, const unsigned char>*, const unsigned char>* sprite_animations){
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[handleAnimation]: Animation index: %d, Frame index: %d, Current_Texture_Loop_Count: %d", animation_properties.Animation_Index, animation_properties.Frame_Index, animation_properties.Current_Texture_Loop_Count);
    const std::pair<Animation_Frame, const unsigned char>* animation = sprite_animations[animation_properties.Animation_Index].first;
    const std::pair<Animation_Frame, const unsigned char>* current_frame = &animation[animation_properties.Frame_Index];
    //if time to display the next frame in the animation
    bool is_frame_changed = false;
    is_frame_changed = animation_properties.Animation_Index != animation_properties.Current_Setting.Cached_Animation_Index;
    if (animation_properties.Current_Texture_Loop_Count > current_frame->second){
        is_frame_changed = true;
        //go to next texture
        animation_properties.Current_Texture_Loop_Count = 1;
        //if no next texture go back to 0; (perplexity suggest, cleverly use remainder operation so anything below last frame will return itself)
        animation_properties.Frame_Index = (animation_properties.Frame_Index + 1) % (sprite_animations[animation_properties.Animation_Index].second + 1);
    }else{animation_properties.Current_Texture_Loop_Count ++;}
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[handleAnimation]: 2, new Frame index: %d, Current_Texture_Loop_Count: %d", animation_properties.Frame_Index, animation_properties.Current_Texture_Loop_Count);
    return {&animation[animation_properties.Frame_Index].first, is_frame_changed};
}