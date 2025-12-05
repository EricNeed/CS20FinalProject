#include<string>
#include<vector>
#include<script_storge/sprite.h>
#include<memory>

class TextureManager{
private:
    //preperation
    TextureManager(){}
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    static std::vector<Sprite&> sprite_list;
public:
    //get only instance
    static TextureManager& getOnlyInstance();

    template<typename DerivedSprite>
    std::pair<long, std::shared_ptr<DerivedSprite>> createSprite(Sprite& new_sprite);
    void removeSpriteFromList(long spriteID);
};