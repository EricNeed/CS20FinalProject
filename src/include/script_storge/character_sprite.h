#pragma once
#include"script_storge/sprite.h"

struct Sprite_Arm{
    //which texture in the texture pool, set to negative to disable arm rendering
    int texture_pool_index = 0;
    //offset from the sprite coordinate
    SDL_Point offset = {0,0};
};

struct Properties_Character : Properties_Base{
    int Health;
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