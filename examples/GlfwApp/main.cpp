#include <zeno/Window.hpp>

int main(int _argc, char** _argv) {
    ze::GLFWContext context{};

    ze::VideoMode mode = ze::VideoMode(800, 600, "Glfw Window");
    ze::Window window;
    if (!window.initialise(mode)) {
        return EXIT_FAILURE;
    }

    bool running = true;

    while (running) {

        ze::Event event;
        window.pumpEvents();
        while (window.pollEvent(event)) {
            if (event.type == ze::Event::EventType::WindowClosed) {
                running = false;
            }
        }

        window.clear();
        window.display();
    }

    window.close();

    return EXIT_SUCCESS;
}