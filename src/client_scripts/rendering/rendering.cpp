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
    sdl_window = SDL_CreateWindow("title", 640, 360, SDL_WINDOW_RESIZABLE);
    sdl_renderer = SDL_CreateRenderer(sdl_window, NULL);
    SDL_SetLogPriority(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_DEBUG);
    SDL_SetRenderLogicalPresentation(sdl_renderer, 640, 360, SDL_LOGICAL_PRESENTATION_OVERSCAN);
    SDL_GetWindowSize(sdl_window, &window_width, &window_height);
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

void ClientRendering::placeInDisplayOrderArray(int y_max, Animation_Properties* propertie){
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


        //update position on screen
        player_properties->Animation.Current_Setting.Current_Texture_FRect.x = static_cast<float>(player_properties->Coord.x - map_screen_cornerX);
        player_properties->Animation.Current_Setting.Current_Texture_FRect.y = static_cast<float>(player_properties->Coord.y - map_screen_cornerY);
        //check if the texture's top left corner is on the screen
        if(pointNotOnScreen(player_properties->Animation.Current_Setting.Current_Texture_FRect.x, player_properties->Animation.Current_Setting.Current_Texture_FRect.y, 32)){continue;}

        //handle animation
        auto [frame_propertie, is_frame_changed] = handleAnimation(player_properties->Animation, sprite_texture_collections[player_properties->Animation.Animation_Collection_Index]);
        //if cannot find texture, load texture, if find, then use it directly
        if(is_frame_changed){
            TextureProperties* texture_properties = getTexture(frame_propertie->Texture_Dir);
            player_properties->Animation.Current_Setting.Current_Texture_FRect.h = texture_properties->height * frame_propertie->size_multiplier;
            player_properties->Animation.Current_Setting.Current_Texture_FRect.w = texture_properties->width * frame_propertie->size_multiplier;
            player_properties->Animation.Current_Setting.Current_Texture_Pointer = texture_properties->texture;
            player_properties->Animation.Current_Setting.Cached_Animation_Index = player_properties->Animation.Animation_Index;
        }

        //place the texture
        placeInDisplayOrderArray(player_properties->Animation.Current_Setting.Current_Texture_FRect.y + player_properties->Animation.Current_Setting.Current_Texture_FRect.h, &player_properties->Animation);
        //rendering result
        //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: texture info: w: %f, h: %f, x: %ld, y: %ld", texture_properties->width, texture_properties->height, player_properties->Coord.x, player_properties->Coord.y);
    }

    for(uint16_t current_index = 0; current_index < order_sorter_max; current_index++){
        Animation_Properties* current_propertie = display_order_sorter[current_index];
        if(!current_propertie){continue;}
        const Animation_Frame* frame_propertie = &sprite_texture_collections[current_propertie->Animation_Collection_Index]->first->first;
        SDL_RenderTextureRotated(sdl_renderer, current_propertie->Current_Setting.Current_Texture_Pointer, nullptr, &current_propertie->Current_Setting.Current_Texture_FRect, 0.0, nullptr, (frame_propertie->Mirror_Horizontally ^ current_propertie->Flip_Horizontally) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    }
    
    SDL_RenderPresent(sdl_renderer);
}


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