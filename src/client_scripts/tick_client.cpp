#include<client/tick_client.h>
#include<server/client_handler.h>
#include<client/player_input.h>



// TickClient::TickClient() : client_handler(ClientHandler::getInstance()), spriteID(client_handler.newConnectedClient()), input_handler(spriteID){
// }

TickClient::TickClient() : client_handler(ClientHandler::getInstance()), spriteID(client_handler.newConnectedClient()){
    ClientInput skibidi_handler(spriteID);
    input_handler = &skibidi_handler;
}

void TickClient::tick_client(){
    while(game_running){
        //handle user input
        input_handler->processUserInput();

        //tick rendering
        client_rendering.tickRender();

        processSDLEvents(sdl_event);
    }
}

void TickClient::processSDLEvents(SDL_Event& sdl_event){
    //process all current SDL events
    while(SDL_PollEvent(&sdl_event)) {
        switch (sdl_event.type){
            //check if player has closed the program
            case SDL_EVENT_QUIT: game_running = false;
        default: break;
        }
    }
}
// class TickClient {
//     private:
//         ClientInput input_handler;
//         ClientRendering client_rendering;

//     public:
//         void tick_client(){
//             //handle user input
//             input_handler.processUserInput();

//             //tick rendering
//             client_rendering.tick_render();
//         }
// };