#pragma once
#include<string>
#include<vector>
#include<SDL3/SDL.h>
#include<script_storge/animation_propertie.h>

class Sprite;
enum class SpriteType;
enum class AncestryTree : uint64_t;

class ClientRendering;

class SpriteManager{
private:
    //preperation
    SpriteManager();
    SpriteManager(const SpriteManager&) = delete;
    SpriteManager& operator=(const SpriteManager&) = delete;

    ClientRendering* client_rendering = nullptr;
public: 
    constexpr static int MAX_SPRITES = 8192;
    Sprite* sprite_list[MAX_SPRITES]{};
    SpriteType id_to_type_list[MAX_SPRITES] = {};

    //get only instance
    static SpriteManager& getOnlyInstance();

    template<typename DerivedSprite>
    std::pair<uint16_t, Sprite*> createSprite(){//pass in de-pointered object mem addr
        //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[SpriteManager]: Creating new sprite");
        uint16_t spriteID = 0;
        while(sprite_list[spriteID] && spriteID < MAX_SPRITES){
            spriteID++;
        }
        //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[SpriteManager]: new sprite ID: %ld", spriteID);
        Sprite* sprite = new DerivedSprite(spriteID);
        sprite_list[spriteID] = sprite;
        return {spriteID, sprite};
    }

    void removeSpriteFromList(uint16_t spriteID);
    bool spriteHaveAncestor(uint64_t spriteID, AncestryTree ancestor);
    void spritePartInitialize(Sprite_Extra_Part* part, int texture_index, bool infront_sprite);
    ~SpriteManager();
};