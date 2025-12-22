#include<script_storge/player.h>

Player::Player(long ID) : Sprite(ID){
    sprite_properties.Type = SpriteType::Player;
    logTypeToSpriteManager();
    sprite_properties.Textures.resize(1);
    sprite_properties.Textures[0] = "resources/textures/sprite.png";
    sprite_properties.WalkSpeed = 10;
}

void Player::logTypeToSpriteManager(){}

const Properties_Player* Player::getProperties(){
    return &sprite_properties;
}