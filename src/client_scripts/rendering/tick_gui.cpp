#include"client/tick_gui.h"


ClientGUI::ClientGUI(){
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ClientGUI::ClientGUI]: constructor running");

    //create all cursor
    SDL_Rect srcrect;
    SDL_Rect dstrect;
    for(uint8_t i = 0; i < Render_Storge::cursor_amount; i++){
        Atlas_Animation texture_animation = Render_Storge::AnimationsInAtlas[Render_Storge::cursor_texture_index[i]].first;
        const Texture_Atlas_Dir_Propertie& texture_dir_propertie = Render_Storge::texture_pool[texture_animation.Texture_Atlas_Index];

        srcrect = {0, texture_dir_propertie.Each_Texture_DimY * texture_animation.Animation_Index_In_Atlas, texture_dir_propertie.Each_Texture_DimX, texture_dir_propertie.Each_Texture_DimY};
        dstrect = {0,0,0,0};
        SDL_Surface* cursor_surface = IMG_Load(texture_dir_propertie.Texture_Atlas_Dir);
        SDL_BlitSurface(cursor_surface, &srcrect, cursor_surface, &dstrect);
        client_cursors[i] = SDL_CreateColorCursor(cursor_surface, 0, 0);

        if(!client_cursors[i]){SDL_LogError(SDL_LOG_CATEGORY_RENDER, "mouse cursor \"%s\" failed to load", texture_dir_propertie.Texture_Atlas_Dir);}
        SDL_DestroySurface(cursor_surface);
    }
}


void ClientGUI::showCursor(uint8_t cursor_index){
    SDL_SetCursor(client_cursors[cursor_index]);
    SDL_ShowCursor();
    
}


void ClientGUI::tickGUI(){

}
