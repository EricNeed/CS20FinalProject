#include<script_storge/character_sprite.h>
#include<cmath>

Player::Player(long ID) : Sprite(ID, &sprite_properties){
    sprite_properties.Type = SpriteType::Player;
    logTypeToSpriteManager();
    sprite_properties.WalkSpeed = 1;
    sprite_properties.Animation.Animation_Collection_Index = 0;
    //SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[Player::Player]: properties address: %p", &sprite_properties);
}

const Properties_Player* Player::getProperties(){
    return &sprite_properties;
}

void Player::whenMovedSprite(int dx, int dy){
    // Better: 0=neg, 1=zero, 2=pos
    int x_dir = (dx > 0) + (dx < 0)*2;
    int y_dir = (dy > 0) + (dy < 0)*2;
    unsigned char animation_index;
    bool flip = false;
    // Pack: x in low bits, y shifted
    switch(x_dir | (y_dir << 2)){  // 0-8 unique values!
        case 1: animation_index = 0; flip = true; break;//right
        case 2: animation_index = 0; break;//left
        //case 4: break;//down
        //case 5: break;//down right
        //case 6: break;//down left
        //case 8: break;//up
        //case 9: break;//up left
    }
    if ((sprite_properties.Animation.Animation_Index != animation_index) || (sprite_properties.Animation.Flip_Horizontally != flip)){
        sprite_properties.Animation.Animation_Index = animation_index;
        sprite_properties.Animation.Frame_Index = 0;
        sprite_properties.Animation.Current_Texture_Loop_Count = 1;
        sprite_properties.Animation.Flip_Horizontally = flip;
    }
};