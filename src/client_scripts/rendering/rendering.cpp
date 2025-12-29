#include<client/rendering.h>
#include"server/sprite_manager.h"
#include"script_storge/sprite.h"
#include<SDL3_image/SDL_image.h>
#include<script_storge/texture_pool.h>

ClientRendering::ClientRendering() : sprite_manager(SpriteManager::getOnlyInstance()){
    sdl_window = SDL_CreateWindow("title", 640, 360, SDL_WINDOW_RESIZABLE);
    sdl_renderer = SDL_CreateRenderer(sdl_window, NULL);
    SDL_SetLogPriority(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_DEBUG);
    SDL_SetRenderLogicalPresentation(sdl_renderer, 640, 360, SDL_LOGICAL_PRESENTATION_OVERSCAN);
}

//load new texture from file
auto ClientRendering::newTexture(const char* texture_dir) -> TextureProperties*{
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::newTexture]: Load texture");
    SDL_Texture *texture_temp = IMG_LoadTexture(sdl_renderer, texture_dir);
    if (!texture_temp){SDL_LogError(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::newTexture]: IMG_LoadTexture error:");}
    SDL_SetTextureScaleMode(texture_temp, SDL_SCALEMODE_NEAREST);
    //cache it
    texture_map[texture_dir] = {texture_temp, static_cast<float>(texture_temp->w), static_cast<float>(texture_temp->h)};
    return &texture_map[texture_dir];
}


void ClientRendering::tickRender(){
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: Render tick start");
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255); 
    SDL_RenderClear(sdl_renderer);

    //render sprite
    for(const auto& sprite : sprite_manager.sprite_list){
        //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: sprite propertie address: %p", sprite->getProperties());
        const Properties_Base* player_properties = sprite->getProperties();
        const Animation_Frame* frame_propertie = handleAnimation(const_cast<Properties_Base*>(player_properties)->Animation, sprite_texture_collections[player_properties->Animation.Animation_Collection_Index]);
        TextureProperties* texture_properties;

        //if cannot find texture, load texture, if find, then use it directly
        if (texture_map.find(frame_propertie->Texture_Dir) == texture_map.end()){
            texture_properties = newTexture(frame_propertie->Texture_Dir);
        }else{
            texture_properties = &texture_map[frame_propertie->Texture_Dir];
        }

        //rendering result
        //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: texture info: w: %f, h: %f, x: %ld, y: %ld", texture_properties->width, texture_properties->height, player_properties->Coord.x, player_properties->Coord.y);
        const SDL_FRect using_frect = {static_cast<float>(player_properties->Coord.x), static_cast<float>(player_properties->Coord.y), texture_properties->width, texture_properties->height};
        SDL_RenderTextureRotated(sdl_renderer, texture_properties->texture, nullptr, &using_frect, 0.0, nullptr, (frame_propertie->Mirror_Horizontally ^ player_properties->Animation.Flip_Horizontally) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
    SDL_RenderPresent(sdl_renderer);
}


void ClientRendering::fullScreenToggle(bool enable_fullscreen){
    SDL_SetWindowFullscreen(sdl_window, enable_fullscreen);
}