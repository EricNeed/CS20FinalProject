#include<client/player_input.h>


ClientInput::ClientInput(long ID){
    keyboard_states = SDL_GetKeyboardState(NULL);
    playerID = ID;
}

void ClientInput::processUserInput(){
    Sprite* current_player = sprite_manager.sprite_list[playerID];
    const Properties_Base* player_properties = current_player->getProperties();
    SDL_Point sprite_position = player_properties->Coord;
    int walk_speed = player_properties->WalkSpeed;

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