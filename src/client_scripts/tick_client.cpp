#include<client/tick_client.h>
#include<server/client_handler.h>
#include<client/player_input.h>


TickClient::TickClient() : client_handler(ClientHandler::getInstance()), client_rendering(ClientRendering::getOnlyInstance(spriteID, true)){
    //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[TickClient::TickClient]: tick client constructor");
    spriteID = client_handler.newConnectedClient();
    input_handler = new ClientInput(spriteID);
}

void TickClient::tick_client(){
    //SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[TickClient::tick_client]: Tick client");

    //handle user input
    input_handler->processUserInput();
    //tick rendering
    //SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[TickClient::tick_client]: Tick render");
    client_rendering.tickRender();
    //SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "[TickClient::tick_client]: end");
}



TickClient::~TickClient(){
    delete input_handler;
}