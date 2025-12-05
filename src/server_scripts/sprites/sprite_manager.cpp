#include<src/include/server/sprite_manager.h>

SpriteManager& SpriteManager::getOnlyInstance(){
    static SpriteManager instance;
    return instance;
}

template<typename DerivedSprite>
std::pair<long, std::shared_ptr<DerivedSprite>> SpriteManager::createSprite(){//pass in de-pointered object mem addr
    auto sprite = std::make_shared<DerivedSprite>
    long spriteID = sprite_list.size();// the size is the last index + 1, so i can directly use it
    sprite_list[spriteID] = sprite;
    return {spriteID, sprite}
}

void SpriteManager::removeSpriteFromList(long spriteID){
    sprite_list[spriteID].reset();
}

// long spriteID = sprite_list.size();// the size is the last index + 1, so i can directly use it
// sprite_list[spriteID] = new_sprite;
// return spriteID;

