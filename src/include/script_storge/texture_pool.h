#pragma once
#include<script_storge/animation_propertie.h>
#include<utility>

inline const Texture_Atlas_Dir_Propertie texture_pool[] = {
    {"resources/textures/sprites/SpriteAtlas.png", 12, 20},
    {"resources/textures/sprites/default/hand_default.png", 5, 5},
    {"resources/textures/cursor/cursor_default.png", 3, 3},
};

//animation frame(std::pair<const char*, const unsigned char>)texture, number of loops prsent this texture
//because how the tick animation system work, the 0th index will play last, and the 1st index will play first

//the length table of each frame in each animation
namespace{
    constexpr uint8_t player_walkS[]{30};
    constexpr uint8_t player_walkSW[]{5,5,5,5};
};



inline static const std::pair<const Atlas_Animation, const uint8_t*> AnimationsInAtlas[]{
    {{0, 0, 1, 3}, (::player_walkSW)},//down left
    {{0, 1, 1, 3}, (::player_walkS)},//down
    {{1, 0, 1, 0}, nullptr},//hand
    {{2, 0, 1, 0}, nullptr},//cursor
};

/***************************************************************************************************************************************************************static textures */
