#include<src/include/client/rendering.h>



class ClientRendering{
    private:
        SDL_Window *sdl_window = SDL_CreateWindow("title", 600, 400, 0);
        SDL_Renderer *sdl_renderer = SDL_CreateRenderer(sdl_window, NULL);

    public:
        ClientRendering(){}

        void tick_render(){}       
};