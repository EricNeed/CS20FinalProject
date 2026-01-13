#include<client/player_input.h>

ClientInput::ClientInput(uint16_t ID){
    keyboard_states = SDL_GetKeyboardState(NULL);
    playerID = ID;
}

void ClientInput::processUserInput(){
    // std::cout << "process user input" << std::endl;
    Sprite* current_player = sprite_manager.sprite_list[playerID];
    const Properties_Base* player_properties = current_player->getProperties();
    int add_x = 0, add_y = 0;
    int walk_speed = player_properties->WalkSpeed;
    
    if(keyboard_states[SDL_SCANCODE_W]){
        add_y += -walk_speed;
        SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "w pressed");
    }
    if(keyboard_states[SDL_SCANCODE_A]){
        add_x += -walk_speed;
        SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "w pressed");
    }
    if(keyboard_states[SDL_SCANCODE_S]){
        add_y += walk_speed;
        SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "w pressed");
    }
    if(keyboard_states[SDL_SCANCODE_D]){
        add_x += walk_speed;
        SDL_LogDebug(SDL_LOG_CATEGORY_INPUT, "w pressed");
    }

    if (add_x != 0 || add_y != 0){
        //SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[ClientInput::processUserInput]: Moving player %ld by (%d, %d)", playerID, add_x, add_y);
        client_handler.newPlayerCoord(playerID, add_x, add_y);
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