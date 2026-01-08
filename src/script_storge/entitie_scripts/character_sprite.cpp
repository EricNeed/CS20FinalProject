#include<script_storge/character_sprite.h>
#include<cmath>

Character::Character(uint16_t ID, bool is_prime, Properties_Character* properties_ptr, SpriteType sprite_type) : Sprite(ID, false, is_prime ? new Properties_Character() : properties_ptr, sprite_type){
    //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Character::Character]: Creating Character with ID %ld", ID);
    is_prime_sprite = is_prime;
    derived_properties = static_cast<Properties_Character*>(propertie_pointer);
    derived_properties->WalkSpeed = 1;
    derived_properties->Animation.Animation_Collection_Index = 0;
    derived_properties->Ancestry_Tree |= static_cast<uint64_t>(AncestryTree::Character);

    //sprite extra part, arm is the case here
    sprite_manager.spritePartInitialize(&derived_properties->Arms[0], 1, true);
    sprite_manager.spritePartInitialize(&derived_properties->Arms[1], 1, true);
    derived_properties->Animation.Current_Setting.Extra_Parts = derived_properties->Arms;
    derived_properties->Animation.Current_Setting.Extra_Part_Amount = 2;
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
        case 1: animation_index = 0; flip = true; break;//right
        case 2: animation_index = 0; break;//left
        case 4: animation_index = 1; break;//down
        //case 5: break;//down right
        //case 6: break;//down left
        //case 8: break;//up
        //case 9: break;//up left
    }
    if ((derived_properties->Animation.Animation_Index != animation_index) || (derived_properties->Animation.Flip_Horizontally != flip)){
        derived_properties->Animation.Animation_Index = animation_index;
        derived_properties->Animation.Frame_Index = 0;
        derived_properties->Animation.Current_Texture_Loop_Count = 1;
        derived_properties->Animation.Flip_Horizontally = flip;
    }
};

Character::~Character(){
    if(is_prime_sprite){
        delete derived_properties;
    }
}