#include<script_storge/player.h>
#include<cmath>

Player::Player(uint16_t ID, bool is_prime, Properties_Player* properties_ptr, SpriteType sprite_type) : Character(ID, false, is_prime ? new Properties_Player() : properties_ptr, sprite_type){
    //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Player::Player]: Creating Player with ID %ld", ID);
    is_prime_sprite = is_prime;
    derived_properties = static_cast<Properties_Player*>(propertie_pointer);
    //SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[Player::Player]: properties address: %p", &sprite_properties);
}

const Properties_Player* Player::getProperties(){
    return derived_properties;
}
Player::~Player(){
    if(is_prime_sprite){
        delete derived_properties;
    }
}