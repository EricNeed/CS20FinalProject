#pragma once
#include<script_storge/animation_propertie.h>

inline const char* texture_pool[] = {
    "resources/textures/sprites/default/SpriteS.png",
    "resources/textures/sprites/default/hand_default.png",
    "resources/textures/sprites/default/SpriteSW.png",
};

//animation frame(std::pair<const char*, const unsigned char>)texture, number of loops prsent this texture
//because how the tick animation system work, the 0th index will play last, and the 1st index will play first
namespace{
    const std::pair<Animation_Frame, const unsigned char> PlayerWalkS[] = {
        {{texture_pool[0], false, 1}, 60},
    };
    const std::pair<Animation_Frame, const unsigned char> PlayerWalkSW[] = {
        {{texture_pool[2], false, 1}, 60},
    };

}

//storge all texture for each sprite types(second is max index):
namespace{
    const std::pair <const std::pair<Animation_Frame, const unsigned char>*, const unsigned char> PlayerAnimations[] = {
        {PlayerWalkS, 0},//remember to update max index when adding new animation
        {PlayerWalkSW, 0},
    };
}


//storge which sprite need which texture collection, please keep in sync with SpriteType enum
inline const std::pair <const std::pair<Animation_Frame, const unsigned char>*, const unsigned char>* sprite_texture_collections[] = {
    PlayerAnimations,
};


/***************************************************************************************************************************************************************static textures */
