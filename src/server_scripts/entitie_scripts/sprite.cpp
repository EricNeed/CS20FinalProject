#include<vector>
#include<string>
#include<SDL3/SDL.h>

class Sprite {
    private:
        static std::vector<Sprite*> sprite_list;
        long spriteID;
        SDL_Point sprite_coord;
    public:
        Sprite(int spriteX, int spriteY){
            spriteID = sprite_list.size();
            sprite_list[spriteID] = this;
            sprite_coord.x = spriteX;
            sprite_coord.y = spriteY;
        }
        ~Sprite(){
            sprite_list[spriteID] = nullptr;
        }
        void moveSprite(int spriteX, int spriteY){
            sprite_coord.x = spriteX;
            sprite_coord.y = spriteY;
        }
        
        int skibidi;

        long getID(){return spriteID;}
};