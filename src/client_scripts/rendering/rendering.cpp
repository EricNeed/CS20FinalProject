#include<client/rendering.h>
#include"server/sprite_manager.h"
#include"script_storge/sprite.h"
#include<SDL3_image/SDL_image.h>

ClientRendering::ClientRendering(){
    sdl_window = SDL_CreateWindow("title", 600, 400, 0);
    sdl_renderer = SDL_CreateRenderer(sdl_window, NULL);
}

TextureProperties ClientRendering::newTexture(std::string texture_dir){
    SDL_Texture *texture_temp = IMG_LoadTexture(sdl_renderer, texture_dir.c_str());
    if (!texture_temp){SDL_Log("IMG_LoadTexture error:");}
    TextureProperties properties = {texture_temp, texture_temp->w, texture_temp->h};
    texture_map[texture_dir] = properties;
    return properties;
}

void ClientRendering::tickRender(){
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255); 
    SDL_RenderClear(sdl_renderer);

    //render sprite
    for(const auto& sprite : sprite_manager.sprite_list){
        const Properties_Base* properties = sprite->getProperties();
        std::string texture_dir = properties->Textures[properties->Current_Texture_Index];
        SDL_Rect sprite_rect = {properties->Coord.x, properties->Coord.y, 32, 32};
        TextureProperties texture_properties;

        //if cannot find texture, load texture, if find, then use it directly
        if (texture_map.find(texture_dir) == texture_map.end()){
            texture_properties = newTexture(texture_dir);
        }else{
            sprite_texture = texture_map[texture_dir];
        }

        SDL_RenderTexture(sdl_renderer, sprite_texture, nullptr, {});
    }

    SDL_RenderPresent(sdl_renderer);
}
