#include<server/sprite_manager.h>
#include"script_storge/sprite.h"
#include"client/rendering.h"

SpriteManager::SpriteManager(){
}

SpriteManager& SpriteManager::getOnlyInstance(){
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "get sprite manager");
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

void SpriteManager::spritePartInitialize(Sprite_Extra_Part* part, int texture_index, bool infront_sprite){
    if(!client_rendering){client_rendering = &ClientRendering::getOnlyInstance(67);}
    TextureProperties* texture_propertie = client_rendering->getTexture(texture_index);
    part->texture = texture_propertie->texture;
    part->frect.h = texture_propertie->height;
    part->frect.w = texture_propertie->width;
    part->Infront_Sprite = infront_sprite;
}

SpriteManager::~SpriteManager(){

}
// uint16_t spriteID = sprite_list.size();// the size is the last index + 1, so i can directly use it
// sprite_list[spriteID] = new_sprite;
// return spriteID;
