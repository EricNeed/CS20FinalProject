#include<client/player_input.h>
#include<iostream>

ClientInput::ClientInput(long ID){
    keyboard_states = SDL_GetKeyboardState(NULL);
    playerID = ID;
}

void ClientInput::processUserInput(){
    // std::cout << "process user input" << std::endl;
    Sprite* current_player = sprite_manager.sprite_list[playerID];
    const Properties_Base* player_properties = current_player->getProperties();
    SDL_Point sprite_position = player_properties->Coord;
    int walk_speed = player_properties->WalkSpeed;
    //SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[ClientInput::processUserInput]: Current player position x: %d, y: %d", sprite_position.x, sprite_position.y);
    if(keyboard_states[SDL_SCANCODE_W]){
        sprite_position.y += walk_speed;
        std::cout << "w pressed" << std::endl;
    }
    if(keyboard_states[SDL_SCANCODE_A]){
        sprite_position.x += walk_speed;
        std::cout << "a pressed" << std::endl;
    }
    if(keyboard_states[SDL_SCANCODE_S]){
        sprite_position.y += -walk_speed;
        std::cout << "s pressed" << std::endl;
    }
    if(keyboard_states[SDL_SCANCODE_D]){
        sprite_position.y += -walk_speed;
        std::cout << "d pressed" << std::endl;
    }

    //client_handler.newPlayerCoord(playerID, sprite_position);
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