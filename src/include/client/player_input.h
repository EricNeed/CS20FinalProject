#include<SDL3/SDL.h>
#include<src/include/script_storge/player.h>
#include<src/include/server/client_handler.h>
#include<server/client_handler.h>

class ClientInput{
    private:
        const bool *keyboard_states;
        Player &player;
    public:
        ClientInput(Player &player_sprite);
        // ClientInput();

        void processUserInput();
};