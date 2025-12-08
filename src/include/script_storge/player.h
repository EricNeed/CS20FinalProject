#pragma once
#include<src/include/script_storge/sprite.h>

class Player : public Sprite{
    private:
        void logTypeToSpriteManager() override;
    public:
        Player(long ID);
};