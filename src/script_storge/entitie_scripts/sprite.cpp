#include<script_storge/sprite.h>

Sprite::Sprite(uint16_t ID, bool is_prime, Properties_Base* properties_ptr, SpriteType sprite_type){
    //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Sprite::Sprite]: Creating Sprite with ID %ld", ID);
    //make so that it use the derived struct instead of current Properties_Base
    if(is_prime){
        propertie_pointer = new Properties_Base();
        is_prime_sprite = false;
    }else{
        propertie_pointer = properties_ptr;
    }
    propertie_pointer->ID = ID;
    propertie_pointer->Type = sprite_type;
    logTypeToSpriteManager();
    //SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[Sprite::Sprite]: properties address: %p", propertie_pointer);
}

void Sprite::logTypeToSpriteManager(){
    sprite_manager.id_to_type_list[propertie_pointer->ID] = propertie_pointer->Type; 
}

void Sprite::placeSprite(SDL_Point new_coord){
    propertie_pointer->Coord = new_coord;
}

void Sprite::moveSprite(int x, int y){
    //SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[Sprite::moveSprite]: Moving sprite %ld from (%d, %d) to (%d, %d)", propertie_pointer->ID, propertie_pointer->Coord.x, propertie_pointer->Coord.y, propertie_pointer->Coord.x + x, propertie_pointer->Coord.y + y);
    propertie_pointer->Coord.x += x;
    propertie_pointer->Coord.y += y;
}

Sprite::~Sprite(){
    if(is_prime_sprite){
        delete propertie_pointer;
    }
}

// class Sprite {
//     protected:
//         static std::vector<Sprite*> sprite_list;
//         long spriteID;
//         SDL_Point sprite_coord;
//         std::vector<std::string> textures;
//     public:
//         Sprite(int spriteX, int spriteY){
//             spriteID = sprite_list.size();// the size is the last index + 1, so i can directly use it
//             sprite_list[spriteID] = this;
//             sprite_coord.x = spriteX;
//             sprite_coord.y = spriteY;
//         }
//         ~Sprite(){
//             sprite_list[spriteID] = nullptr;
//         }
//         void moveSprite(int spriteX, int spriteY){
//             sprite_coord.x = spriteX;
//             sprite_coord.y = spriteY;
//         }

//         long getID(){return spriteID;}
// };