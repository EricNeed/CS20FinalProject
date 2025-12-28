#include<script_storge/sprite.h>

Sprite::Sprite(long ID, Properties_Base* properties_ptr) {
    //make so that it use the derived struct instead of current Properties_Base
    derived_properties = properties_ptr;
    derived_properties->ID = ID;
    //SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[Sprite::Sprite]: properties address: %p", derived_properties);
}

// Sprite::~Sprite(){
// }

void Sprite::logTypeToSpriteManager(){
    sprite_manager.id_to_type_list.resize(derived_properties->ID + 1);
    sprite_manager.id_to_type_list[derived_properties->ID] = derived_properties->Type;
    
}

void Sprite::placeSprite(SDL_Point new_coord){
    derived_properties->Coord = new_coord;
}

void Sprite::moveSprite(int x, int y){
    //SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[Sprite::moveSprite]: Moving sprite %ld from (%d, %d) to (%d, %d)", derived_properties->ID, derived_properties->Coord.x, derived_properties->Coord.y, derived_properties->Coord.x + x, derived_properties->Coord.y + y);
    derived_properties->Coord.x += x;
    derived_properties->Coord.y += y;
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