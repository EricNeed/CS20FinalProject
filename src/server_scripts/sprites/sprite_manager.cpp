#include<src/include/server/sprite_manager.h>

SpriteManager& SpriteManager::getOnlyInstance(){
    static SpriteManager instance;
    return instance;
}

template<typename DerivedSprite>
std::pair<long, Sprite*> SpriteManager::createSprite(){//pass in de-pointered object mem addr
    long spriteID = sprite_list.size();// the size is the last index + 1, so i can directly use it
    Sprite* sprite = new DerivedSprite(spriteID)
    sprite_list[spriteID] = sprite;
    return {spriteID, sprite}
}

void SpriteManager::removeSpriteFromList(long spriteID){
    delete sprite_list[spriteID];
    sprite_list[spriteID] = nullptr;
}


// long spriteID = sprite_list.size();// the size is the last index + 1, so i can directly use it
// sprite_list[spriteID] = new_sprite;
// return spriteID;

