#include "SDL3/SDL.h"

class ClientRendering{
    private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    
    public:
        ClientRendering(SDL_Window* window);
        void tick_render();     
};