#include<string>
#include<vector>
#include<script_storge/sprite.h>

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
    std::pair<long, Sprite*> createSprite();

    void removeSpriteFromList(long spriteID);
};