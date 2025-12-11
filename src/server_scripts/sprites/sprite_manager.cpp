#include<server/sprite_manager.h>
#include"script_storge/sprite.h"

//cancel forward declearation for errors
std::vector<Sprite*> SpriteManager::sprite_list;
std::vector<SpriteType> SpriteManager::id_to_type_list;

SpriteManager& SpriteManager::getOnlyInstance(){
    static SpriteManager instance;
    return instance;
}

void SpriteManager::removeSpriteFromList(long spriteID){
    delete sprite_list[spriteID];
    sprite_list[spriteID] = nullptr;
}

// long spriteID = sprite_list.size();// the size is the last index + 1, so i can directly use it
// sprite_list[spriteID] = new_sprite;
// return spriteID;

