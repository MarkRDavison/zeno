#include <zeno/Window.hpp>
#include <zeno/Graphics.hpp>

int main(int _argc, char** _argv) {
    ze::GLFWContext context{};

    ze::VideoMode mode = ze::VideoMode(800, 600, "Zeno Graphics");
    mode.contextMajor = 4;
    mode.contextMinor = 5;
    ze::Window window;
    if (!window.initialise(mode)) {
        return EXIT_FAILURE;
    }

    const ze::Vector2f size(static_cast<float>(mode.width), static_cast<float>(mode.height));

    if (!ze::Shader::createDefaultShaders()){
        return EXIT_FAILURE;
    }

#ifdef UNIX
#ifdef APPLE
    const std::string fontPath = "/Library/Fonts/arial.ttf";
#else
    const std::string fontPath = "$home/.fonts/arial.ttf";
#endif
#else
    const std::string fontPath = "C:/Windows/Fonts/arial.ttf";
#endif


    ze::Font fontDefault = ze::Font(ze::Font::FontType::Default);
    if (!fontDefault.loadFromFile(fontPath, 64, ze::Font::FontType::Default)) {
        return EXIT_FAILURE;
    }
    ze::Font fontSdf = ze::Font(ze::Font::FontType::SignedDistanceField);
    if (!fontSdf.loadFromFile(fontPath, 64, ze::Font::FontType::SignedDistanceField)) {
        return EXIT_FAILURE;
    }

    ze::Text textDefault("Hello world - default", &fontDefault, 64);
    textDefault.setInternalColour(ze::Colour::Green);
    textDefault.centerText();
    ze::Text textSdf("Hello world - sdf", &fontSdf, 64);
    textSdf.setInternalColour(ze::Colour::Cyan);
    textSdf.setExternalColour(ze::Colour::Blue);
    textSdf.setOutlineThickness(2.0f);
    textSdf.centerText();

    ze::VertexArray lines = ze::VertexArray(ze::DrawType::LineStrip);

    lines.appendVertex(ze::Vertex(ze::Vector2f(-size.x / 2.0f + 20.0f, -100.0f), ze::Colour::Blue));
    lines.appendVertex(ze::Vertex(ze::Vector2f(-size.x / 2.0f + 20.0f, 0.0f), ze::Colour::Green));
    lines.appendVertex(ze::Vertex(ze::Vector2f(+size.x / 2.0f - 20.0f, 0.0f), ze::Colour::Green));
    lines.appendVertex(ze::Vertex(ze::Vector2f(+size.x / 2.0f - 20.0f, +100.0f), ze::Colour::Blue));

    lines.create();

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
        info.projection = ze::Mat4x4::Orthographic3D(-size.x / 2.0f, +size.x / 2.0f, +size.y / 2.0f, -size.y / 2.0f, -1.0f, +1.0f);
        info.model.translate(ze::Vector3f(0.0f, 128.0f, 0.0f));
        textDefault.render(window, info);
        info.model.translate(ze::Vector3f(0.0f, -128.0f, 0.0f));
        lines.render(window, info);
        info.model.translate(ze::Vector3f(0.0f, -128.0f, 0.0f));
        textSdf.render(window, info);

        window.display();
    }

    window.close();

    return EXIT_SUCCESS;
}