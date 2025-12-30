#include<server/sprite_manager.h>
#include"script_storge/sprite.h"

SpriteManager& SpriteManager::getOnlyInstance(){
    static SpriteManager instance;
    return instance;
}

void SpriteManager::removeSpriteFromList(uint16_t spriteID){
    delete sprite_list[spriteID];
    sprite_list[spriteID] = nullptr;
}

// uint16_t spriteID = sprite_list.size();// the size is the last index + 1, so i can directly use it
// sprite_list[spriteID] = new_sprite;
// return spriteID;

