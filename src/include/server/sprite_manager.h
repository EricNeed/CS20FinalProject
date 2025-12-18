#pragma once
#include<string>
#include<vector>

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
        sprite_list[spriteID] = sprite;
        return {spriteID, sprite};
    }

    void removeSpriteFromList(long spriteID);
};