#include<script_storge/player.h>

Player::Player(long ID) : Sprite(ID, &sprite_properties){
    sprite_properties.Type = SpriteType::Player;
    logTypeToSpriteManager();
    sprite_properties.Texture_Collection_Index = static_cast<int>(SpriteType::Player);
    sprite_properties.Current_Texture_Index = 0;
    sprite_properties.WalkSpeed = 10;
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[Player::Player]: properties address: %p", &sprite_properties);
}

const Properties_Base* Player::getProperties(){
    return &sprite_properties;
}

const Properties_Player* Player::getSpecialProperties(){
    return &sprite_properties;
}