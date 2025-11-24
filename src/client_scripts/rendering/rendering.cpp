#include "SDL3/SDL.h"

class SDL_Rendering{
    private:
    SDL_Renderer *sdl_renderer;
    public:
        SDL_Rendering(SDL_Window* window){
            sdl_renderer = SDL_CreateRenderer(window, NULL);
        }

        void tick_render(){
            
        }       
};