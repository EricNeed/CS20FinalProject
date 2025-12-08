#pragma once
#include<src/include/script_storge/sprite.h>

class Player : public Sprite{
    Player(long ID);
    void logTypeToSpriteManager() override;
};