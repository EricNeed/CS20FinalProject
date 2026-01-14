#include"client/tick_gui.h"


ClientGUI::ClientGUI(){
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ClientGUI::ClientGUI]: constructor running");
    //create all cursor
    for(uint8_t i = 0; i < cursor_amount; i++){
        SDL_Surface* cursor_surface = IMG_Load("resources/textures/sprites/SpriteAtlas.png");
        if(!SDL_SetCursor(SDL_CreateColorCursor(cursor_surface, 1, 1))){}
        SDL_DestroySurface(cursor_surface);
    }
    SDL_ShowCursor();
}



void ClientGUI::tickGUI(){

}