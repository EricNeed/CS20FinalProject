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

struct Animation_Frame{
    const char* Texture_Dir;
    bool Mirror_Horizontally = false;
    //multiply the length and width not the area
    unsigned char size_multiplier = 1;
};

struct Animation_Properties{
    short Animation_Collection_Index = 0;
    //which animation currently on
    unsigned char Animation_Index = 0;
    //which frame(texture) in the animation
    unsigned char Frame_Index = 0;
    //how many loops has presented this texture(one based)
    unsigned char Current_Texture_Loop_Count = 1;
    //flip everything in current animation horizontally
    bool Flip_Horizontally = false;
};

//inter the sprite's propertie and the sprite's animation sequence array to get the current texture to use
inline const Animation_Frame* handleAnimation(Animation_Properties& animation_properties, const std::pair <const std::pair<Animation_Frame, const unsigned char>*, const unsigned char>* sprite_animations){
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[handleAnimation]: Animation index: %d, Frame index: %d, Current_Texture_Loop_Count: %d", animation_properties.Animation_Index, animation_properties.Frame_Index, animation_properties.Current_Texture_Loop_Count);
    const std::pair<Animation_Frame, const unsigned char>* animation = sprite_animations[animation_properties.Animation_Index].first;
    const std::pair<Animation_Frame, const unsigned char>* current_frame = &animation[animation_properties.Frame_Index];
    //if time to display the next frame in the animation
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[handleAnimation]: 1");
    if (animation_properties.Current_Texture_Loop_Count > current_frame->second){
        //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[handleAnimation]: 1.1");
        //go to next texture
        animation_properties.Current_Texture_Loop_Count = 1;
        //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[handleAnimation]: 1.2");
        //if no next texture go back to 0; (perplexity suggest, cleverly use remainder operation so anything below last frame will return itself)
        animation_properties.Frame_Index = (animation_properties.Frame_Index + 1) % (sprite_animations[animation_properties.Animation_Index].second + 1);
        //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[handleAnimation]: 1.3");
    }else{animation_properties.Current_Texture_Loop_Count ++;}
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[handleAnimation]: 2, new Frame index: %d, Current_Texture_Loop_Count: %d", animation_properties.Frame_Index, animation_properties.Current_Texture_Loop_Count);
    return &animation[animation_properties.Frame_Index].first;
}