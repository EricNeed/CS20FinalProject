#pragma once
const char* texture_pool[] = {
    "resources/textures/sprite.png",
};

//storge all texture for each sprite types:
const char* PlayerTextures[1] = {
    texture_pool[0],
};

//storge which sprite need which texture collection, please keep in sync with SpriteType enum
const char** sprite_texture_collections[1] = {
    PlayerTextures,
};