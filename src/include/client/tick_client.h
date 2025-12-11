#pragma once
#include<SDL3/SDL.h>
#include<client/player_input.h>
#include<client/rendering.h>

class TickClient {
    private:
        ClientInput input_handler;
        ClientRendering client_rendering;
    public:
        void tick_client();
};