#include <iostream>

#include "Window.h"

int main (int argc, char** argv) { 

    auto window = Window::Create(800, 800, "toxic");

    window->renderLoop();
    return 0;
}