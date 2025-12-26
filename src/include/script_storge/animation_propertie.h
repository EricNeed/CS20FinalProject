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
    bool Mirror = false;
    //multiply the length and width not the area
    unsigned char size_multiplier = 1;
};

struct Animation_Properties{
    //which animation currently on
    unsigned char Animation_Index = 0;
    //which frame(texture) in the animation
    unsigned char Frame_Index = 0;
    //how many loops has presented this texture(one based)
    unsigned char Current_Texture_Loop_Count = 1;
};

//inter the sprite's propertie and the sprite's animation sequence array to get the current texture to use
inline const Animation_Frame* handleAnimation(Animation_Properties& animation_properties, const std::pair <const std::pair<Animation_Frame, const unsigned char>*, const unsigned char>* sprite_animations){
    const std::pair<Animation_Frame, const unsigned char>* animation = sprite_animations[animation_properties.Animation_Index].first;
    const std::pair<Animation_Frame, const unsigned char>* current_frame = &animation[animation_properties.Frame_Index];
    //if time to display the next frame in the animation
    if (animation_properties.Current_Texture_Loop_Count > current_frame->second){
        //go to next texture
        animation_properties.Current_Texture_Loop_Count = 1;
        //if no next texture go back to 0; (perplexity suggest, cleverly use remainder operation so anything below last frame will return itself)
        animation_properties.Frame_Index = (animation_properties.Frame_Index + 1) % sprite_animations[animation_properties.Animation_Index].second;
    }else{animation_properties.Current_Texture_Loop_Count ++;}
    return &animation[animation_properties.Frame_Index].first;
}