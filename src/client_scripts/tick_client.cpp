#include<src/include/client/tick_client.h>

void TickClient::tick_client(){
    //handle user input
    input_handler.processUserInput();

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