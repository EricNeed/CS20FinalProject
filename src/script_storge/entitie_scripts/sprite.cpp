#include<src/include/script_storge/sprite.h>

Sprite::Sprite(long ID){
    spriteID = ID;
}

Sprite::~Sprite(){
}

void Sprite::moveSprite(int spriteX, int spriteY){
    sprite_coord.x = spriteX;
    sprite_coord.y = spriteY;
}

long Sprite::getID(){return spriteID;}
SpriteType Sprite::getType(){return sprite_type;}




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