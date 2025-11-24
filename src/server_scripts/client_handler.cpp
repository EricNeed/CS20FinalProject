#include<SDL3/SDL.h>
#include<unordered_map>
#include<string>

class ClientHandler{
    private:
        ClientHandler(){}
        ClientHandler(const ClientHandler&) = delete;
        ClientHandler& operator=(const ClientHandler&) = delete;

        std::unordered_map<std::string, SDL_Point> player_coordinate;
    public:
        static ClientHandler& getInstance(){
            static ClientHandler instance;
            return instance;
        }

        std::unordered_map<std::string, SDL_Point>& getPlayerCoords(){return player_coordinate;}

        void update_player_coord(std::string player_name, SDL_Point new_coord){
            player_coordinate[player_name] = new_coord;
        }
        
};