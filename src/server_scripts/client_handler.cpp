#include<server/client_handler.h>

ClientHandler& ClientHandler::getInstance(){
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "get client handler intance");
    static ClientHandler instance;
    return instance;
}

void processClientRequest(){
    
}

void ClientHandler::newPlayerCoord(uint16_t player_spriteID, int add_x, int add_y){
    Player* player = static_cast<Player*>(sprite_manager.sprite_list[player_spriteID]);
    player->moveSprite(add_x, add_y);
    player->whenMovedSprite(add_x, add_y);
}

long ClientHandler::newConnectedClient(){
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ClientHandler::newConnectedClient]: New client connected");
    auto [spriteID, pPlayer] = sprite_manager.createSprite<Player>();
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[ClientHandler::newConnectedClient]: New client spriteID: %ld", spriteID);
    pPlayer->placeSprite({10,10});
    return spriteID;
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