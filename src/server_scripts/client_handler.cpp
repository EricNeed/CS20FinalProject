#include<src/include/server/client_handler.h>

ClientHandler& ClientHandler::getInstance(){
    static ClientHandler instance;
    return instance;
}

void processClientRequest(){
    
}

void ClientHandler::newPlayerCoord(std::string player_name, SDL_Point new_coord){
    player_coordinate[player_name] = new_coord;
}

void ClientHandler::newConnectedClient(){
    sprite_manager.createSprite<Player>();
}
 



// class ClientHandler{
//     private:
//         ClientHandler(){}
//         ClientHandler(const ClientHandler&) = delete;
//         ClientHandler& operator=(const ClientHandler&) = delete;

//         std::unordered_map<std::string, SDL_Point> player_coordinate;
//     public:
//         static ClientHandler& getInstance(){
//             static ClientHandler instance;
//             return instance;
//         }

//         std::unordered_map<std::string, SDL_Point>& getPlayerCoords(){return player_coordinate;}

//         void update_player_coord(std::string player_name, SDL_Point new_coord){
//             player_coordinate[player_name] = new_coord;
//         }
        
// };