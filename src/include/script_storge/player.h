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

        const Properties_Player* getProperties() override;

        void whenMovedSprite(int x, int y);
};