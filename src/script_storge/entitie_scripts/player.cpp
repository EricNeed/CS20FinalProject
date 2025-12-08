#include<script_storge/player.h>

Player::Player(long ID) : Sprite(ID){
    sprite_type = SpriteType::Player;
    logTypeToSpriteManager();
}

void Player::logTypeToSpriteManager(){
    spriter_manager.id_to_type_list[spriteID] = SpriteType::Player;
}