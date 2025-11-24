#include<src

class TickServer{
    private:
        ClientHandler& client_handler = ClientHandler::getInstance();
        std::unordered_map<std::string, SDL_Point>& player_coord_update = client_handler.getPlayerCoords();

    public:
        void ticking(){
            //move each player to their new location
            for (const auto& [key, value] : player_coord_update){
                
            }
        }
};