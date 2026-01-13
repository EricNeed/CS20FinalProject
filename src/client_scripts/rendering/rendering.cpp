#include<client/rendering.h>
#include"server/sprite_manager.h"
#include"script_storge/sprite.h"
#include<SDL3_image/SDL_image.h>
#include<span>
#include<cstring>
#include<script_storge/user_data.h>

ClientRendering& ClientRendering::getOnlyInstance(uint16_t ID, bool is_first_call){
    static ClientRendering instance;
    if(is_first_call){instance.playerID = ID;}
    return instance;
}

ClientRendering::ClientRendering() : sprite_manager(SpriteManager::getOnlyInstance()){
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ClientRendering::ClientRendering]: constructor runs");
    texture_map = new SDL_Texture*[TEXTURE_MAP_MAX]{};
    display_order_sorter = new Properties_Base*[order_sorter_max];
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

void ClientRendering::renderDrawSimple(Atlas_Animation animation, SDL_FRect& dstrect, uint8_t frame_index){
    const Texture_Atlas_Dir_Propertie& texture_proeprties = texture_pool[animation.Texture_Atlas_Index];
    static SDL_FRect srcrect = {(float)(texture_proeprties.Each_Texture_DimX * frame_index), (float)(texture_proeprties.Each_Texture_DimY * animation.Animation_Index_In_Atlas), (float)texture_proeprties.Each_Texture_DimX, (float)texture_proeprties.Each_Texture_DimY};
    dstrect.h = (float)(texture_proeprties.Each_Texture_DimY * animation.size_multiplier);
    dstrect.w = (float)(texture_proeprties.Each_Texture_DimX * animation.size_multiplier);
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::renderSpriteParts]: srcrect:[%.1f,%.1f,%.1f,%.1f], distrect:[%.1f,%.1f,%.1f,%.1f], texture index:%ld", part_srcrect.x, part_srcrect.y, part_srcrect.w, part_srcrect.h, part_dstrect.x, part_dstrect.y, part_dstrect.w, part_dstrect.h, animation.Texture_Atlas_Index);
    
    SDL_RenderTexture(sdl_renderer, getTexture(animation.Texture_Atlas_Index), &srcrect, &dstrect);
};

void ClientRendering::fullScreenToggle(bool enable_fullscreen){
    SDL_SetWindowFullscreen(sdl_window, enable_fullscreen);
}

/******************************************************************************************************************************************************************main tick render */
void ClientRendering::tickRender(){
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: Render tick start");
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255); 
    SDL_RenderClear(sdl_renderer);

    std::memset(display_order_sorter, 0, order_sorter_max * sizeof(Properties_Base*));

    //uppdate view port position on the map base on player position
    const SDL_Point* player_coord = &sprite_manager.sprite_list[playerID]->getProperties()->Coord;
    map_screen_cornerX = player_coord->x - window_width / 2;
    map_screen_cornerY = player_coord->y - window_height / 2;
    //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: current sprite public position (%ld, %ld)", player_map_coordX, player_map_coordY);

    renderFloorTiles();
    renderSprite();
    renderCursor();
    
    SDL_RenderPresent(sdl_renderer);
}
/******************************************************************************************************************************************************************render sprite */
void ClientRendering::renderSprite(){
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

        //handle animation
        bool is_frame_changed  = handleAnimation(player_animation);
        const Atlas_Animation& current_animation = AnimationsInAtlas[player_animation.Animation_Index].first;

        SDL_Texture* texture_current = getTexture(current_animation.Animation_Index_In_Atlas);

        //if cannot find texture, load texture, if find, then use it directly
        if(is_frame_changed){
            //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: changed, frame(%ld)", player_animation.Frame_Index);
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
 
        renderSpriteParts(player_properties, false);

        //render the main sprite body
        const Texture_Atlas_Dir_Propertie& frame_dimention = texture_pool[current_propertie.Cached_Animation->Texture_Atlas_Index];
        frame_srcrect = {(float)frame_dimention.Each_Texture_DimX * current_propertie.Frame_Index, (float)(frame_dimention.Each_Texture_DimY * current_propertie.Cached_Animation->Animation_Index_In_Atlas), (float)frame_dimention.Each_Texture_DimX, (float)frame_dimention.Each_Texture_DimY};

        //SDL_LogDebug(SDL_LOG_CATEGORY_RENDER, "[ClientRendering::tickRender]: srcrect:[%.1f,%.1f,%.1f,%.1f], distrect:[%.1f,%.1f,%.1f,%.1f], texture index:%ld", frame_srcrect.x, frame_srcrect.y, frame_srcrect.w, frame_srcrect.h, current_propertie->Current_Texture_FRect.x, current_propertie->Current_Texture_FRect.y, current_propertie->Current_Texture_FRect.w, current_propertie->Current_Texture_FRect.h, current_propertie->Cached_Animation->Animation_Index_In_Atlas);
        SDL_RenderTextureRotated(sdl_renderer, texture_map[current_propertie.Cached_Animation->Texture_Atlas_Index], &frame_srcrect, &current_propertie.Current_Texture_FRect, 0.0, nullptr, (current_propertie.Flip_Horizontally) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

        renderSpriteParts(player_properties, true);
    }
}


void ClientRendering::renderSpriteParts(Properties_Base* sprite_properties, bool infront){
    for(uint8_t i = 0; i < sprite_properties->Extra_Part_Amount; i++){
        Sprite_Extra_Part& extra_part = sprite_properties->Extra_Part_Array[i];
        if(infront == extra_part.Infront_Sprite){
            renderTextureSimple(AnimationsInAtlas[extra_part.Animaton_Index].first, part_dstrect, 0);
        }
    }
}
/******************************************************************************************************************************************************************render ui */
void ClientRendering::renderCursor(){
    SDL_MouseButtonFlags buttons = SDL_GetMouseState(&cursorX, &cursorY);

    SDL_RenderTexture();
}


/******************************************************************************************************************************************************************render ui */
void ClientRendering::renderFloorTiles(){

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