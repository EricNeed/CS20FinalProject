#include<src/include/server/tick_server_main.h>
#include<server/sprite_manager.h>
TickServer::TickServer(){
    auto [spriteID, pPlayer] = sprite_manager.createSprite<Character>();
}

void TickServer::ticking(){
    
}

// class TickServer{
//     private:
//         ClientHandler& client_handler = ClientHandler::getInstance();
//         std::unordered_map<std::string, SDL_Point>& player_coord_update = client_handler.getPlayerCoords();

//     public:
//         void ticking(){
//             //move each player to their new location
//             for (const auto& [key, value] : player_coord_update){
                
//             }
//         }
// };