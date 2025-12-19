#include<script_storge/player.h>

Player::Player(long ID) : Sprite(ID){
    sprite_properties.Type = SpriteType::Player;
    logTypeToSpriteManager();
    sprite_properties.Textures[0] = "resources/textures/sprite.png";
}

void Player::logTypeToSpriteManager(){}

const Properties_Player* Player::getProperties(){
    return &sprite_properties;
}