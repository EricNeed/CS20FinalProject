#include<src/include/client/player_input.h>


ClientInput::ClientInput(Player &player_sprite): player(player_sprite){
    keyboard_states = SDL_GetKeyboardState(NULL);
}

void ClientInput::processUserInput(){
    if(keyboard_states[SDL_SCANCODE_W]){          
    }
    if(keyboard_states[SDL_SCANCODE_A]){
    }
    if(keyboard_states[SDL_SCANCODE_S]){
    }
    if(keyboard_states[SDL_SCANCODE_D]){
    }
}



// class ClientInput{
//     private:
//         const bool *keyboard_states = SDL_GetKeyboardState(NULL);
//         Player &player;

//     public:
//         ClientInput(Player &player_sprite): player(player_sprite){
//         }
//         // ClientInput(){}

//         void processUserInput(){
//             if(keyboard_states[SDL_SCANCODE_W]){
                
//             }
//             if(keyboard_states[SDL_SCANCODE_A]){
//             }
//             if(keyboard_states[SDL_SCANCODE_S]){
//             }
//             if(keyboard_states[SDL_SCANCODE_D]){
//             }
//         }
// };