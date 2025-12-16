#include<script_storge/player.h>

Player::Player(long ID) : Sprite(ID){
    sprite_properties.Type = SpriteType::Player;
    logTypeToSpriteManager();
    sprite_properties.Textures[0] = "resources/textures/sprite.png";
}

void Player::logTypeToSpriteManager(){
    sprite_manager.id_to_type_list[sprite_properties.ID] = SpriteType::Player;
}