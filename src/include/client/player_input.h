#include<SDL3/SDL.h>
#include<src/include/script_storge/player.h>
#include<src/include/server/client_handler.h>
#include<server/client_handler.h>
#include<server/sprite_manager.h>

class ClientInput{
    private:
        const bool *keyboard_states;
        long playerID;
        SpriteManager& sprite_manager = SpriteManager::getOnlyInstance();
    public:
        ClientInput(long ID);
        // ClientInput();

        void processUserInput();
};