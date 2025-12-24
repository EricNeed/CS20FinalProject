#include<client/tick_client.h>
#include<server/client_handler.h>
#include<client/player_input.h>


// TickClient::TickClient() : client_handler(ClientHandler::getInstance()), spriteID(client_handler.newConnectedClient()), input_handler(spriteID){
// }

TickClient::TickClient() : client_handler(ClientHandler::getInstance()){
    spriteID = client_handler.newConnectedClient();
    input_handler = new ClientInput(spriteID);
}

void TickClient::tick_client(){
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Tick client");

    //handle user input
    input_handler->processUserInput();
    //tick rendering
    client_rendering.tickRender();
}



TickClient::~TickClient(){
    delete input_handler;
}