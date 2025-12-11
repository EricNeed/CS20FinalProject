#include<client/player_input.h>


ClientInput::ClientInput(long ID){
    keyboard_states = SDL_GetKeyboardState(NULL);
    playerID = ID;
}

void ClientInput::processUserInput(){
    Sprite* current_player = sprite_manager.sprite_list[playerID];
    SDL_Point sprite_position = current_player->getCoord();
    int walk_speed = current_player->getSpeed();

    if(keyboard_states[SDL_SCANCODE_W]){
        sprite_position.y += walk_speed;
    }
    if(keyboard_states[SDL_SCANCODE_A]){
        sprite_position.x += walk_speed;
    }
    if(keyboard_states[SDL_SCANCODE_S]){
        sprite_position.y += -walk_speed;
    }
    if(keyboard_states[SDL_SCANCODE_D]){
        sprite_position.y += -walk_speed;
    }
    client_handler.newPlayerCoord(playerID, sprite_position);
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