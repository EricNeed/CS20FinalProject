#include<script_storge/character_sprite.h>
#include<cmath>

Character::Character(uint16_t ID, bool is_prime, Properties_Character* properties_ptr, SpriteType sprite_type, uint8_t extra_part_amount) : Sprite(ID, false, is_prime ? new Properties_Character() : properties_ptr, sprite_type, extra_part_amount+3){
    //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Character::Character]: Creating Character with ID %ld", ID);
    is_prime_sprite = is_prime;
    derived_properties = static_cast<Properties_Character*>(propertie_pointer);
    derived_properties->WalkSpeed = 1;
    derived_properties->Ancestry_Tree |= static_cast<uint64_t>(AncestryTree::Character);

    //sprite extra part, arm is the case here, 0 is left, +1 is right
    extra_part_start_index = extra_part_amount;
    derived_properties->Extra_Part_Array[extra_part_amount].Animaton_Index = 2;
    derived_properties->Extra_Part_Array[extra_part_amount+1].Animaton_Index = 2;

    //extra gears
    derived_properties->Extra_Part_Array[extra_part_amount+2].Animaton_Index = 4;

}

const Properties_Character* Character::getProperties(){
    return derived_properties;
}


void Character::whenMovedSprite(int dx, int dy){
    // Better: 0=neg, 1=zero, 2=pos
    int x_dir = (dx > 0) + (dx < 0)*2;
    int y_dir = (dy > 0) + (dy < 0)*2;
    unsigned char animation_index;
    bool flip = false;
    // Pack: x in low bits, y shifted
    switch(x_dir | (y_dir << 2)){  // 0-8 unique values!
        case 1: updateAnimation(0, true, true, true); break;//right
        case 2: updateAnimation(0, false, true, true); break;//left
        case 4: updateAnimation(1, false, true, true); break;//down
        //case 5: break;//down right
        //case 6: break;//down left
        //case 8: break;//up
        //case 9: break;//up left
    }
};


void Character::updateAnimation(uint16_t animation_index, bool flip, bool left_hand_infront, bool right_hand_infront){
    if(animation_index ^ derived_properties->Animation.Animation_Index){
        derived_properties->Animation.Frame_Index = 0;
        derived_properties->Animation.Current_Texture_Loop_Count = 1;
    }
    
    derived_properties->Animation.Animation_Index = animation_index;
    derived_properties->Animation.Flip_Horizontally = flip;

    derived_properties->Extra_Part_Array[extra_part_start_index].Infront_Sprite = left_hand_infront;
    derived_properties->Extra_Part_Array[extra_part_start_index+1].Infront_Sprite = right_hand_infront;
};


Character::~Character(){
    if(is_prime_sprite){
        delete derived_properties;
    }
}