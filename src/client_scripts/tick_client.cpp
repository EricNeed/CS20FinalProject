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
    //handle user input
    input_handler->processUserInput();

    //tick rendering
    client_rendering.tick_render();
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