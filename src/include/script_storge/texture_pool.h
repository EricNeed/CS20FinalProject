#pragma once
#include<script_storge/animation_propertie.h>
#include<utility>

//the length table of each frame in each animation
namespace{
    constexpr uint8_t player_walk[]{5,5,5};
};

namespace Render_Storge{
    inline const Texture_Atlas_Dir_Propertie texture_pool[] = {
        {"resources/textures/sprites/SpriteAtlas.png", 12, 20},
        {"resources/textures/sprites/hand_default.png", 3, 3},
        {"resources/textures/cursor/cursor_default.png", 9,9},
        {"resources/textures/tool/holding_musket.png", 20, 5},
        {"resources/textures/landscape/temp_landscape.png", 256, 128},
    };

    //animation frame(std::pair<const char*, const unsigned char>)texture, number of loops prsent this texture
    //because how the tick animation system work, the 0th index will play last, and the 1st index will play first
    inline static const std::pair<const Atlas_Animation, const uint8_t*> AnimationsInAtlas[]{
        {{0, 0, 1, 2}, (::player_walk)},//down left
        {{0, 1, 1, 2}, (::player_walk)},//down
        {{1, 0, 1, 0}, nullptr},//hand
        {{2, 0, 1, 0}, nullptr},//cursor
        {{3, 0, 1, 0}, nullptr}, //musket in hand
        {{0, 2, 1, 2}, (::player_walk)},//left
        {{0, 4, 1, 2}, (::player_walk)},//up left
        {{0, 3, 1, 2}, (::player_walk)},//up
        {{4, 0, 6, 0}, nullptr}, //temporary landscape
    };


/***************************************************************************************************************************************************************static textures */
    inline static const uint8_t cursor_texture_index[]{3};
    const uint8_t cursor_amount = sizeof(cursor_texture_index);
};