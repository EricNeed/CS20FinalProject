#pragma once
#include"script_storge/sprite.h"

struct Properties_Player : Properties_Base{

};

class Player : public Sprite{
    private:
        Properties_Player sprite_properties;
        void logTypeToSpriteManager() override;
    public:
        Player(long ID);

        const Properties_Player* getProperties() override;

};