#include<src/include/server/client_handler.h>

class TickServer{
    private:
        ClientHandler& client_handler = ClientHandler::getInstance();

    public:
        TickServer();
        void ticking();
};