#include<src/include/client/player_input.h>


ClientInput::ClientInput(long ID){
    keyboard_states = SDL_GetKeyboardState(NULL);
    playerID = ID;
}

void ClientInput::processUserInput(){
    SDL_Point sprite_offset;
    sprite_offset.x = 0;
    sprite_offset.y = 0;
    int walk_speed = sprite_manager.sprite_list[playerID]->walk_speed;

    if(keyboard_states[SDL_SCANCODE_W]){
        sprite_offset.y += walk_speed;
    }
    if(keyboard_states[SDL_SCANCODE_A]){
        sprite_offset.x += walk_speed;
    }
    if(keyboard_states[SDL_SCANCODE_S]){
        sprite_offset.y += -walk_speed;
    }
    if(keyboard_states[SDL_SCANCODE_D]){
        sprite_offset.y += -walk_speed;
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