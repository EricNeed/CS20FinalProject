#include <iostream>
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"


SDL_Window *sdl_window = SDL_CreateWindow("title", 600, 400, 0);
SDL_Renderer *sdl_renderer = SDL_CreateRenderer(sdl_window, NULL);
const bool *keyboard_states = SDL_GetKeyboardState(NULL);

bool running = true;
/********************************************************************data type */
struct Sprite {
    SDL_Texture *texture;
    SDL_FRect rect;
};

/********************************************************************tool functions */
Sprite loadSDLTexture(const char* texture_dir, float image_weith, float imag_hight){
    SDL_Texture *texture_temp = IMG_LoadTexture(sdl_renderer, texture_dir);
    if (!texture_temp){SDL_Log("IMG_LoadTexture error:");}
    Sprite sprite;
    sprite.texture = texture_temp;
    sprite.rect = {0, 0, image_weith, imag_hight};
    return sprite;
}

/********************************************************************helper functions */
void processSDLEvents(SDL_Event& sdl_event){
    //process all current SDL events
    while(SDL_PollEvent(&sdl_event)) {
        switch (sdl_event.type){
            //check if player has closed the program
            case SDL_EVENT_QUIT: running = false;
        default: break;
        }
    }
}

void processUserInput(Sprite& player){

    if(keyboard_states[SDL_SCANCODE_W]){
        player.rect.y --;
    }
    if(keyboard_states[SDL_SCANCODE_A]){
        player.rect.x --;
    }
    if(keyboard_states[SDL_SCANCODE_S]){
        player.rect.y ++;
    }
    if(keyboard_states[SDL_SCANCODE_D]){
        player.rect.x ++;
    }
}
/********************************************************************main functions */
void loop(){
    SDL_Event sdl_event;

    Sprite dude = loadSDLTexture("resources\\textures\\man.jpg", 40, 40);

    while(running){
        //process keyboard input
        processUserInput(dude);

        //update video frame
        SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255); 
        SDL_RenderClear(sdl_renderer);
        SDL_RenderTexture(sdl_renderer, dude.texture, nullptr, &dude.rect);
        SDL_RenderPresent(sdl_renderer);

        //process sdl events
        processSDLEvents(sdl_event);

        //game ticking
        SDL_Delay(16);  // Sleep ~16ms (~60 FPS), prevents high CPU usage
    }
}

int main(){
    std::cout << "SDL Test Main Running..." << std::endl;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    loop();

    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
    return 0;
}