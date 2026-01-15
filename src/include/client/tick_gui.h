#pragma once
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include"script_storge/texture_pool.h"

class ClientGUI{
    private: 
        //cursor
        SDL_Cursor* client_cursors[Render_Storge::cursor_amount];
    public:
        ClientGUI();
        void showCursor(uint8_t cursor_index);
        void tickGUI();
};