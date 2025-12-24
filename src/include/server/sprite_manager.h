#pragma once
#include<string>
#include<vector>
#include<SDL3/SDL.h>

class Sprite;
enum class SpriteType;

class SpriteManager{
private:
    //preperation
    SpriteManager(){}
    SpriteManager(const SpriteManager&) = delete;
    SpriteManager& operator=(const SpriteManager&) = delete;

public: 

    static std::vector<Sprite*> sprite_list;
    static std::vector<SpriteType> id_to_type_list;

    //get only instance
    static SpriteManager& getOnlyInstance();

    template<typename DerivedSprite>
    std::pair<long, Sprite*> createSprite(){//pass in de-pointered object mem addr
        long spriteID = sprite_list.size();// the size is the last index + 1, so i can directly use it
        Sprite* sprite = new DerivedSprite(spriteID);
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[SpriteManager]: Created sprite, address %p", sprite);
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[SpriteManager]: SpriteManager, address %p", this);
        sprite_list.resize(spriteID + 1, nullptr);
        sprite_list[spriteID] = sprite;
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[SpriteManager]: sprite in list, address %p", sprite_list[spriteID]);
        return {spriteID, sprite};
    }

    void removeSpriteFromList(long spriteID);
};