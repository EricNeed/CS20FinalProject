#include<script_storge/animation_propertie.h>
#include<script_storge/texture_pool.h>
#include<utility>

bool handleAnimation(Animation_Properties& animation_properties){
    const std::pair<const Atlas_Animation, const uint8_t*>* animation = &Animations[animation_properties.Animation_Index];
    bool is_frame_changed = animation_properties.Animation_Index != animation_properties.Cached_Animation_Index;
    //if time to display the next frame in the animation
    if(animation->second[animation_properties.Frame_Index] > animation_properties.Current_Texture_Loop_Count){
        is_frame_changed = true;
        //go to next texture
        animation_properties.Current_Texture_Loop_Count = 1;
        //if no next texture go back to 0; (perplexity suggest, cleverly use remainder operation so anything below last frame will return itself)
        animation_properties.Frame_Index = (animation_properties.Frame_Index + 1) % (animation->first.Frame_Max_Index + 1);
    }else{animation_properties.Current_Texture_Loop_Count ++;}
    return is_frame_changed;
}