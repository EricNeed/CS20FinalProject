#pragma once
#include<script_storge/animation_propertie.h>

const char* texture_pool[] = {
    "resources/textures/sprite.png",
    "resources/textures/hand_default.png"
};


//animation frame(std::pair<const char*, const unsigned char>)texture, number of loops prsent this texture
//because how the tick animation system work, the 0th index will play last, and the 1st index will play first
const std::pair<Animation_Frame, const unsigned char> PlayerWalk[] = {
    {{texture_pool[0], false, 1}, 60},
};

//storge all texture for each sprite types(second is max index):
const std::pair <const std::pair<Animation_Frame, const unsigned char>*, const unsigned char> PlayerAnimations[] = {
    {PlayerWalk, 0},//remember to update max index when adding new animation
};

//storge which sprite need which texture collection, please keep in sync with SpriteType enum
const std::pair <const std::pair<Animation_Frame, const unsigned char>*, const unsigned char>* sprite_texture_collections[] = {
    PlayerAnimations,
};


/***************************************************************************************************************************************************************static textures */
