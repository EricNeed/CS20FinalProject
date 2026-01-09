#pragma once
#include<script_storge/animation_propertie.h>

inline const Texture_Atlas_Dir_Propertie texture_pool[] = {
    {"E:/code/c++/CS20Final/CS20FinalProject/build/resources/textures/sprites/SpriteAtlas.png", 12, 20},
    {"resources/textures/sprites/default/hand_default.png", 5, 5},
};

//animation frame(std::pair<const char*, const unsigned char>)texture, number of loops prsent this texture
//because how the tick animation system work, the 0th index will play last, and the 1st index will play first

//the length table of each frame in each animation
namespace{
    uint8_t player_walkS[]{30};
    uint8_t player_walkSW[]{30,30,30,30};
    uint8_t hand_default[]{255};
};



inline const std::pair<const Atlas_Animation, const uint8_t*> Animations[]{
    {{0, 0, 1, 3}, player_walkSW},//down left
    {{0, 1, 1, 3}, player_walkS},//down
    {{0, 0, 1, 0}, hand_default},//hand
};

/***************************************************************************************************************************************************************static textures */
