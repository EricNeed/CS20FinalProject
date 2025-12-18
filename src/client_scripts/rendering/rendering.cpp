#include<client/rendering.h>
#include"server/sprite_manager.h"
#include"script_storge/sprite.h"
#include<SDL3_image/SDL_image.h>

ClientRendering::ClientRendering() : sprite_manager(SpriteManager::getOnlyInstance()){
    sdl_window = SDL_CreateWindow("title", 600, 400, 0);
    sdl_renderer = SDL_CreateRenderer(sdl_window, NULL);
}
auto ClientRendering::newTexture(std::string texture_dir) -> TextureProperties{
    SDL_Texture *texture_temp = IMG_LoadTexture(sdl_renderer, texture_dir.c_str());
    if (!texture_temp){SDL_Log("IMG_LoadTexture error:");}
    //cache it
    TextureProperties properties = {texture_temp, static_cast<float>(texture_temp->w), static_cast<float>(texture_temp->h)};
    texture_map[texture_dir] = properties;
    return properties;
}

void ClientRendering::tickRender(){
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255); 
    SDL_RenderClear(sdl_renderer);

    //render sprite
    for(const auto& sprite : sprite_manager.sprite_list){
        const Properties_Base* player_properties = sprite->getProperties();
        std::string texture_dir = player_properties->Textures[player_properties->Current_Texture_Index];
        TextureProperties texture_properties;

        //if cannot find texture, load texture, if find, then use it directly
        if (texture_map.find(texture_dir) == texture_map.end()){
            texture_properties = newTexture(texture_dir);
        }else{
            texture_properties = texture_map[texture_dir];
        }

        //rendering result
        const SDL_FRect using_frect = {static_cast<float>(player_properties->Coord.x), static_cast<float>(player_properties->Coord.y), texture_properties.width, texture_properties.height};
        SDL_RenderTexture(sdl_renderer, texture_properties.texture, nullptr, &using_frect);
    }
    SDL_RenderPresent(sdl_renderer);
}

