// src/web_main.cpp
#include "web_interface.hpp"

WebInterface* interface = nullptr;

void mainLoop() {
    if (interface) {
        interface->render();
        interface->handleInput();
    }
}

int main() {
    interface = new WebInterface();
    interface->init();
    
    emscripten_set_main_loop(mainLoop, 0, 1);
    
    return 0;
}