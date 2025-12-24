#pragma once
#include"script_storge/sprite.h"

struct Properties_Player : Properties_Base{
    int Health;
};

class Player : public Sprite{
    private:
        void logTypeToSpriteManager() override{Sprite::logTypeToSpriteManager();};
        Properties_Player sprite_properties;
    public:
        Player(long ID);

        const Properties_Base* getProperties() override;
        const Properties_Player* getSpecialProperties() override;
        void moveSprite(SDL_Point new_coord) override {
            Sprite::moveSprite(new_coord);
        }

};