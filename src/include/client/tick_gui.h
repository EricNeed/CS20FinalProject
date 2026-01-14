#pragma once
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include"script_storge/texture_pool.h"

class ClientGUI{
    private: 
        //cursor
        SDL_Cursor* client_cursors[cursor_amount];
    public:
        ClientGUI();
        void tickGUI();
};