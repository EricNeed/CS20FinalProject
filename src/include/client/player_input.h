#include <SDL3/SDL.h>
#include<src/include/player.h>

class ClientInput{
    private:
        const bool *keyboard_states;
        Player &player;
    public:
        ClientInput(Player &player_sprite);

        void processUserInput();
};