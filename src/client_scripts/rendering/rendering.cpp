#include<client/rendering.h>
#include"server/sprite_manager.h"
#include"script_storge/sprite.h"
#include<SDL3_image/SDL_image.h>
#include<span>

ClientRendering::ClientRendering() : sprite_manager(SpriteManager::getOnlyInstance()){
    sdl_window = SDL_CreateWindow("title", 640, 360, SDL_WINDOW_RESIZABLE);
    sdl_renderer = SDL_CreateRenderer(sdl_window, NULL);
    SDL_SetLogPriority(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_DEBUG);
    SDL_SetRenderLogicalPresentation(sdl_renderer, 640, 360, SDL_LOGICAL_PRESENTATION_OVERSCAN);
}

//load new texture from file
void ClientRendering::newTexture(const char* texture_dir){
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::newTexture]: Load texture");
    SDL_Texture *texture_temp = IMG_LoadTexture(sdl_renderer, texture_dir);
    if (!texture_temp){SDL_LogError(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::newTexture]: IMG_LoadTexture error:");}
    SDL_SetTextureScaleMode(texture_temp, SDL_SCALEMODE_NEAREST);
    //cache it
    texture_map[texture_dir] = {texture_temp, static_cast<float>(texture_temp->w), static_cast<float>(texture_temp->h)};
}

TextureProperties* ClientRendering::getTexture(const char* texture_dir){
    if (texture_map.find(texture_dir) == texture_map.end()){
        newTexture(texture_dir);
    }
    return &texture_map[texture_dir];
}

void ClientRendering::tickRender(){
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: Render tick start");
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255); 
    SDL_RenderClear(sdl_renderer);

    //render sprite
    for(const auto& sprite : std::span(sprite_manager.sprite_list, sprite_manager.MAX_SPRITES - 1)){
        if(!sprite){continue;}
        //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: sprite propertie address: %p", sprite->getProperties());
        Properties_Base* player_properties = const_cast<Properties_Base*>(sprite->getProperties());
        auto [frame_propertie, is_frame_changed] = handleAnimation(player_properties->Animation, sprite_texture_collections[player_properties->Animation.Animation_Collection_Index]);
        //if cannot find texture, load texture, if find, then use it directly
        if(is_frame_changed){
            TextureProperties* texture_properties = getTexture(frame_propertie->Texture_Dir);
            player_properties->Animation.Current_Setting.Current_Texture_FRect.h = texture_properties->height * frame_propertie->size_multiplier;
            player_properties->Animation.Current_Setting.Current_Texture_FRect.w = texture_properties->width * frame_propertie->size_multiplier;
            player_properties->Animation.Current_Setting.Current_Texture_Pointer = texture_properties->texture;
        }

        player_properties->Animation.Current_Setting.Current_Texture_FRect.x = static_cast<float>(player_properties->Coord.x);
        player_properties->Animation.Current_Setting.Current_Texture_FRect.y = static_cast<float>(player_properties->Coord.y);

        //rendering result
        //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: texture info: w: %f, h: %f, x: %ld, y: %ld", texture_properties->width, texture_properties->height, player_properties->Coord.x, player_properties->Coord.y);
        SDL_RenderTextureRotated(sdl_renderer, player_properties->Animation.Current_Setting.Current_Texture_Pointer, nullptr, &player_properties->Animation.Current_Setting.Current_Texture_FRect, 0.0, nullptr, (frame_propertie->Mirror_Horizontally ^ player_properties->Animation.Flip_Horizontally) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
    SDL_RenderPresent(sdl_renderer);
}


void ClientRendering::fullScreenToggle(bool enable_fullscreen){
    SDL_SetWindowFullscreen(sdl_window, enable_fullscreen);
}