#include<src/include/server/client_handler.h>

class TickServer{
    private:
        ClientHandler& client_handler = ClientHandler::getInstance();
        SpriteManager& sprite_manager = SpriteManager::getOnlyInstance();
    public:
        TickServer();
        void ticking();
};