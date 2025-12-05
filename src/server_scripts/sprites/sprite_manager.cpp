#include<src/include/server/sprite_manager.h>

TextureManager& TextureManager::getOnlyInstance(){
    static TextureManager instance;
    return instance;
}

template<typename DerivedSprite>
std::pair<long, std::shared_ptr<DerivedSprite>> TextureManager::createSprite(Sprite& new_sprite){//pass in de-pointered object mem addr
    auto sprite = std::make_shared<DerivedSprite>
    long spriteID = sprite_list.size();// the size is the last index + 1, so i can directly use it
    sprite_list[spriteID] = sprite;
    return {spriteID, sprite}
}

void TextureManager::removeSpriteFromList(long spriteID){

}

// long spriteID = sprite_list.size();// the size is the last index + 1, so i can directly use it
// sprite_list[spriteID] = new_sprite;
// return spriteID;