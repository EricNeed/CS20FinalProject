#include<string>
#include<vector>
#include<script_storge/sprite.h>
#include<memory>

class SpriteManager{
private:
    //preperation
    SpriteManager(){}
    SpriteManager(const SpriteManager&) = delete;
    SpriteManager& operator=(const SpriteManager&) = delete;

    static std::vector<std::shared_ptr<Sprite>> sprite_list;
public:
    //get only instance
    static SpriteManager& getOnlyInstance();

    template<typename DerivedSprite>
    std::pair<long, std::shared_ptr<DerivedSprite>> createSprite();
    void removeSpriteFromList(long spriteID);
};