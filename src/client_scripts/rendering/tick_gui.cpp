#include"client/tick_gui.h"


ClientGUI::ClientGUI(){
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ClientGUI::ClientGUI]: constructor running");
    //create all cursor
    for(uint8_t i = 0; i < Render_Storge::cursor_amount; i++){
        const Texture_Atlas_Dir_Propertie& texture_dir_propertie = Render_Storge::texture_pool[Render_Storge::cursor_texture_index[i]];
        SDL_Surface* cursor_surface = IMG_Load(texture_dir_propertie.Texture_Atlas_Dir);
        if(!SDL_SetCursor(SDL_CreateColorCursor(cursor_surface, texture_dir_propertie.Each_Texture_DimX, texture_dir_propertie.Each_Texture_DimY))){}
        SDL_DestroySurface(cursor_surface);
    }
    SDL_ShowCursor();
}



void ClientGUI::tickGUI(){

}