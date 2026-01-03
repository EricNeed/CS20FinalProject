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

bool SpriteManager::spriteHaveAncestor(uint64_t spriteID, AncestryTree ancestor){
    uint64_t ancestry_type64 = static_cast<uint64_t>(ancestor);
    return (sprite_list[spriteID]->getProperties()->Ancestry_Tree & ancestry_type64) == ancestry_type64;
}
// uint16_t spriteID = sprite_list.size();// the size is the last index + 1, so i can directly use it
// sprite_list[spriteID] = new_sprite;
// return spriteID;

