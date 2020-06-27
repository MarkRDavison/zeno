#include <zeno/Window.hpp>
#include <zeno/Graphics.hpp>

int main(int _argc, char** _argv) {
    ze::GLFWContext context{};

    ze::VideoMode mode = ze::VideoMode(800, 600, "Zeno Window");
    ze::Window window;
    if (!window.initialise(mode)) {
        return EXIT_FAILURE;
    }

    const ze::Vector2f size(static_cast<float>(mode.width), static_cast<float>(mode.height));

    ze::Shader::createDefaultShaders();

    ze::CircleShape c(64.0f);
    c.setInternalColour(ze::Colour::Green);
    c.setOutlineColour(ze::Colour::Magenta);
    c.setOutlineThickness(8.0f);

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

        ze::RenderInfo info;
        info.projection = ze::Mat4x4::Orthographic3D(-size.x/2.0f, +size.x/2.0f, +size.y / 2.0f, -size.y / 2.0f, -1.0f, +1.0f);

        c.render(window, info);

        window.display();
    }

    window.close();

    return EXIT_SUCCESS;
}