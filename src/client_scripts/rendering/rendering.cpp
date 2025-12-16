#include<client/rendering.h>
#include<server/sprite_manager.h>

ClientRendering::ClientRendering(){
    sdl_window = SDL_CreateWindow("title", 600, 400, 0);
    sdl_renderer = SDL_CreateRenderer(sdl_window, NULL);
}

void ClientRendering::tick_render(){
    //render sprite
    for(const auto& sprite : sprite_manager.sprite_list){
        //sprite
    }
}
