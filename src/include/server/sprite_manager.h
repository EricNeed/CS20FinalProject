#pragma once
#include<string>
#include<vector>
#include<iostream>

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
        std::cout << "create srpite running\n" << std::endl;
        long spriteID = sprite_list.size();// the size is the last index + 1, so i can directly use it
        std::cout << "making new sprite \n" << std::endl;
        Sprite* sprite = new DerivedSprite(spriteID);
        std::cout << "chache sprite \n" << std::endl;
        
        sprite_list[spriteID] = sprite;
        return {spriteID, sprite};
    }

    void removeSpriteFromList(long spriteID);
};