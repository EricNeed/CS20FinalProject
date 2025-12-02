#pragma once
#include <SDL3/SDL.h>
#include<src/include/script_storge/player.h>

class ClientInput{
    private:
        const bool *keyboard_states = SDL_GetKeyboardState(NULL);
        Player &player;
    public:
        ClientInput(Player &player_sprite): player(player_sprite){
        }

        void processUserInput(){
            if(keyboard_states[SDL_SCANCODE_W]){
                
            }
            if(keyboard_states[SDL_SCANCODE_A]){
            }
            if(keyboard_states[SDL_SCANCODE_S]){
            }
            if(keyboard_states[SDL_SCANCODE_D]){
            }
        }
};