#include<client/rendering.h>
#include"server/sprite_manager.h"
#include"script_storge/sprite.h"
#include<SDL3_image/SDL_image.h>
#include<span>
#include<cstring>

ClientRendering& ClientRendering::getOnlyInstance(uint16_t ID, bool is_first_call){
    static ClientRendering instance;
    if(is_first_call){instance.playerID = ID;}
    return instance;
}

ClientRendering::ClientRendering() : sprite_manager(SpriteManager::getOnlyInstance()){
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ClientRendering::ClientRendering]: constructor runs");
    texture_map = new SDL_Texture*[TEXTURE_MAP_MAX]{};
    sdl_window = SDL_CreateWindow("title", 640, 360, SDL_WINDOW_RESIZABLE);
    sdl_renderer = SDL_CreateRenderer(sdl_window, NULL);
    SDL_SetLogPriority(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_DEBUG);
    SDL_SetRenderLogicalPresentation(sdl_renderer, 640, 360, SDL_LOGICAL_PRESENTATION_OVERSCAN);
    SDL_GetWindowSize(sdl_window, &window_width, &window_height);
}

//load new texture from file
void ClientRendering::newTexture(uint16_t texture_dir_index){
    SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::newTexture]: Load texture, dir: %s", texture_pool[texture_dir_index].Texture_Atlas_Dir);
    SDL_Texture *texture_temp = IMG_LoadTexture(sdl_renderer, texture_pool[texture_dir_index].Texture_Atlas_Dir);
    if (!texture_temp){SDL_LogError(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::newTexture]: IMG_LoadTexture error:");}
    SDL_SetTextureScaleMode(texture_temp, SDL_SCALEMODE_NEAREST);
    //cache it
    texture_map[texture_dir_index] = texture_temp;
}

SDL_Texture* ClientRendering::getTexture(uint16_t texture_dir_index){
    if (!texture_map[texture_dir_index]){
        newTexture(texture_dir_index);
    }
    return texture_map[texture_dir_index];
}

void ClientRendering::placeInDisplayOrderArray(int y_max, Properties_Base* propertie){
    if(y_max < 0){return;}
    if (!display_order_sorter[y_max])[[likely]]{ display_order_sorter[y_max] = propertie; return; }
    if (!display_order_sorter[y_max-1])[[likely]]{ display_order_sorter[y_max-1] = propertie; return; }
    if (!display_order_sorter[y_max+1])[[likely]]{ display_order_sorter[y_max+1] = propertie; return; }
    if (!display_order_sorter[y_max-2])[[likely]]{ display_order_sorter[y_max-2] = propertie; return; }
    if (!display_order_sorter[y_max+2])[[likely]]{ display_order_sorter[y_max+2] = propertie; return; }
}

void ClientRendering::tickRender(){
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: Render tick start");
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255); 
    SDL_RenderClear(sdl_renderer);

    std::memset(display_order_sorter, 0, sizeof(display_order_sorter));

    //uppdate view port position on the map base on player position
    const SDL_Point* player_coord = &sprite_manager.sprite_list[playerID]->getProperties()->Coord;
    player_map_coordX = player_coord->x;
    player_map_coordY = player_coord->y;
    map_screen_cornerX = player_map_coordX - window_width / 2;
    map_screen_cornerY = player_map_coordY - window_height / 2;
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: current sprite public position (%ld, %ld)", player_map_coordX, player_map_coordY);

    //render sprite
    for(const auto& sprite : std::span(sprite_manager.sprite_list, sprite_manager.MAX_SPRITES - 1)){
        if(!sprite){continue;}
        //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: sprite propertie address: %p", sprite->getProperties());

        Properties_Base* player_properties = const_cast<Properties_Base*>(sprite->getProperties());
        Animation_Properties& player_animation = player_properties->Animation;

        //update position on screen
        player_animation.Current_Texture_FRect.x = static_cast<float>(player_properties->Coord.x - map_screen_cornerX);
        player_animation.Current_Texture_FRect.y = static_cast<float>(player_properties->Coord.y - map_screen_cornerY);
        //check if the texture's top left corner is on the screen
        if(pointNotOnScreen(player_animation.Current_Texture_FRect.x, player_animation.Current_Texture_FRect.y, 32)){continue;}
        //player_animation.Extra_Parts->frect.x = player_animation.Current_Setting.Current_Texture_FRect.x + player_animation.Current_Setting.Extra_Parts->offset.x;
        //player_animation.Extra_Parts->frect.y = player_animation.Current_Setting.Current_Texture_FRect.y + player_animation.Current_Setting.Extra_Parts->offset.y;
        //handle animation
        bool is_frame_changed  = handleAnimation(player_animation);
        const Atlas_Animation& current_animation = AnimationsInAtlas[player_animation.Animation_Index].first;

        SDL_Texture* texture_current = getTexture(current_animation.Animation_Index_In_Atlas);

        //if cannot find texture, load texture, if find, then use it directly
        if(is_frame_changed){
            SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: changed, frame(%ld)", player_animation.Frame_Index);
            player_animation.Current_Texture_FRect.w = texture_pool[current_animation.Texture_Atlas_Index].Each_Texture_DimX * current_animation.size_multiplier;
            player_animation.Current_Texture_FRect.h = texture_pool[current_animation.Texture_Atlas_Index].Each_Texture_DimY * current_animation.size_multiplier;
            player_animation.Cached_Animation_Index = player_animation.Animation_Index;
            player_animation.Cached_Animation = &const_cast<Atlas_Animation&>(current_animation);
        }

        //place the texture
        placeInDisplayOrderArray(player_animation.Current_Texture_FRect.y + player_animation.Current_Texture_FRect.h, player_properties);
    }
    //rendering
    static SDL_FRect frame_srcrect;
    for(uint16_t current_index = 0; current_index < order_sorter_max; current_index++){
        Properties_Base* player_properties = display_order_sorter[current_index];
        if(!player_properties){continue;}
        Animation_Properties& current_propertie = player_properties->Animation;
        for(uint8_t i = 0; i < current_propertie.; i++){

        }
        //render the main sprite body
        const Texture_Atlas_Dir_Propertie& frame_dimention = texture_pool[current_propertie.Cached_Animation->Texture_Atlas_Index];
        frame_srcrect = {static_cast<float>(frame_dimention.Each_Texture_DimX * current_propertie.Frame_Index), static_cast<float>(frame_dimention.Each_Texture_DimY * current_propertie.Cached_Animation->Animation_Index_In_Atlas), static_cast<float>(frame_dimention.Each_Texture_DimX), static_cast<float>(frame_dimention.Each_Texture_DimY)};
        //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: srcrect:[%.1f,%.1f,%.1f,%.1f], distrect:[%.1f,%.1f,%.1f,%.1f], texture index:%ld", frame_srcrect.x, frame_srcrect.y, frame_srcrect.w, frame_srcrect.h, current_propertie->Current_Texture_FRect.x, current_propertie->Current_Texture_FRect.y, current_propertie->Current_Texture_FRect.w, current_propertie->Current_Texture_FRect.h, current_propertie->Cached_Animation->Animation_Index_In_Atlas);
        SDL_RenderTextureRotated(sdl_renderer, texture_map[current_propertie.Cached_Animation->Texture_Atlas_Index], &frame_srcrect, &current_propertie.Current_Texture_FRect, 0.0, nullptr, (current_propertie.Flip_Horizontally) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
    
    SDL_RenderPresent(sdl_renderer);
}
//[ClientRendering::tickRender]: srcrect:[0.0,20.0,12.0,20.0], distrect:[310.0,170.0,12.0,20.0], texture index:-115419136

void ClientRendering::fullScreenToggle(bool enable_fullscreen){
    SDL_SetWindowFullscreen(sdl_window, enable_fullscreen);
}

/*ill keep this version because i like it
void ClientRendering::placeInDisplayOrderArray(int y_max, Display_Propertie* propertie){
    if(y_max < 0){return;}
    if(!display_order_sorter[y_max]){display_order_sorter[y_max] = propertie; return;}

    //if y_max index is occupied then find the closest nullptr index to y_max
    char perfered_index = 100;
    for(char i = -2; i < 3; i++){
        if(!display_order_sorter[y_max + i] && perfered_index > abs(i)){
            perfered_index = i;
        }
    }

    if(perfered_index == 100){return;}
    display_order_sorter[perfered_index] = propertie;
}
*/

/*for(uint16_t current_index = 0; current_index < order_sorter_max; current_index++){
        Animation_Properties* current_propertie = display_order_sorter[current_index];
        if(!current_propertie){continue;}
        //load extra parts behind sprite
        for(uint8_t i = 0; i < current_propertie->Current_Setting.Extra_Part_Amount; i++){
            //update the parts position
            extra_part_array[i].frect.x = current_propertie->Current_Setting.Current_Texture_FRect.x + extra_part_array[i].offset.x;
            extra_part_array[i].frect.y = current_propertie->Current_Setting.Current_Texture_FRect.y + extra_part_array[i].offset.y;
            if(!extra_part_array[i].Infront_Sprite){
                SDL_RenderTexture(sdl_renderer, extra_part_array[i].texture, nullptr, &extra_part_array[i].frect);
            }
        }
        const Animation_Frame* frame_propertie = &sprite_texture_collections[current_propertie->Animation_Collection_Index]->first->first;
        SDL_RenderTextureRotated(sdl_renderer, current_propertie->Current_Setting.Current_Texture_Pointer, nullptr, &current_propertie->Current_Setting.Current_Texture_FRect, 0.0, nullptr, (frame_propertie->Mirror_Horizontally ^ current_propertie->Flip_Horizontally) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        //load extra part infront of sprite
        for(uint8_t i = 0; i < current_propertie->Current_Setting.Extra_Part_Amount; i++){
            if(extra_part_array[i].Infront_Sprite){SDL_RenderTexture(sdl_renderer, extra_part_array[i].texture, nullptr, &extra_part_array[i].frect);}
        }
    }*/