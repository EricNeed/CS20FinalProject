#include<script_storge/player.h>

Player::Player(long ID) : Sprite(ID, &sprite_properties){
    sprite_properties.Type = SpriteType::Player;
    logTypeToSpriteManager();
    sprite_properties.WalkSpeed = 1;
    //SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[Player::Player]: properties address: %p", &sprite_properties);
}

const Properties_Player* Player::getProperties(){
    return &sprite_properties;
}