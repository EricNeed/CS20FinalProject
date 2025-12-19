#include<script_storge/sprite.h>
#include<iostream>

Sprite::Sprite(long ID){
    sprite_properties.ID = ID;
}

// Sprite::~Sprite(){
// }

void Sprite::logTypeToSpriteManager(){
    std::cout << sprite_properties.ID << std::endl;
    sprite_manager.id_to_type_list.resize(sprite_properties.ID + 1);
    sprite_manager.id_to_type_list[sprite_properties.ID] = sprite_properties.Type;
}

void Sprite::moveSprite(SDL_Point new_coord){
    sprite_properties.Coord = new_coord;
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