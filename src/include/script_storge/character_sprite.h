#pragma once
#include"script_storge/sprite.h"

struct Properties_Character : Properties_Base{
    int Health;
    Sprite_Extra_Part Arms[2] = {{1,{0,0}, true}, {1,{12,0}, true}};
};

class Character : public Sprite{
    private:
        Properties_Character* derived_properties;
        bool is_prime_sprite = false;
    public:
        Character(uint16_t ID, bool is_prime = true, Properties_Character* properties_ptr = nullptr, SpriteType sprite_type = SpriteType::Character);

        const Properties_Character* getProperties() override;
        void whenMovedSprite(int x, int y);
        ~Character();
};