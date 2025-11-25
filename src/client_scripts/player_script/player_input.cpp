#include <SDL3/SDL.h>

class ClientInput{
    private:
        const bool *keyboard_states = SDL_GetKeyboardState(NULL);
    public:
        ClientInput(auto player_sprite){
            
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