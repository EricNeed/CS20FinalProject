#pragma once
#include"script_storge/character_sprite.h"

struct Properties_Player : Properties_Character{
};

class Player : public Character{
    private:
        Properties_Player* derived_properties;
        bool is_prime_sprite = false;
    public:
        Player(long ID, bool is_prime = true, Properties_Player* properties_ptr = nullptr, SpriteType sprite_type = SpriteType::Player);

        const Properties_Player* getProperties() override;
        ~Player();
};