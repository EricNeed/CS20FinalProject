#pragma once
#include"script_storge/sprite.h"

struct Properties_Character : Properties_Base{
    int Health;
    //Sprite_Extra_Part Arms[2];
};

class Character : public Sprite{
    private:
        Properties_Character* derived_properties;
        bool is_prime_sprite = false;
        uint8_t extra_part_start_index;
        
        void updateAnimation(uint16_t animation_index, bool flip, bool left_hand_infront, bool right_hand_infront);
    public:
        Character(uint16_t ID, bool is_prime = true, Properties_Character* properties_ptr = nullptr, SpriteType sprite_type = SpriteType::Character, uint8_t extra_part_amount = 0);

        const Properties_Character* getProperties() override;
        void whenMovedSprite(int x, int y);
        ~Character();
};