#include <zeno/Window.hpp>
#include <zeno/Graphics.hpp>

int main(int _argc, char** _argv) {
    ze::GLFWContext context{};

    ze::VideoMode mode = ze::VideoMode(800, 640, "Zeno Graphics");
    mode.contextMajor = 4;
    mode.contextMinor = 5;
    ze::Window window;
    if (!window.initialise(mode)) {
        return EXIT_FAILURE;
    }

    ze::Vector2f size(window.getSize());

    if (!ze::Shader::createDefaultShaders()){
        return EXIT_FAILURE;
    }

#ifdef UNIX
#ifdef APPLE
    std::string fontPath = "/Library/Fonts/arial.ttf";
#else
    std::string fontPath = "$home/.fonts/arial.ttf";
#endif
#else
    std::string fontPath = "C:/Windows/Fonts/arial.ttf";
#endif
    if (_argc == 2) {
        fontPath = _argv[1];
    }

    ze::Font fontDefault = ze::Font(ze::Font::FontType::Default);
    if (!fontDefault.loadFromFile(fontPath, 128, ze::Font::FontType::Default)) {
        std::cerr << "Failed to load font, you can pass a path to a font to this executable" << std::endl;
        return EXIT_FAILURE;
    }
    ze::Font fontSdf = ze::Font(ze::Font::FontType::SignedDistanceField);
    if (!fontSdf.loadFromFile(fontPath, 64, ze::Font::FontType::SignedDistanceField)) {
        std::cerr << "Failed to load font, you can pass a path to a font to this executable" << std::endl;
        return EXIT_FAILURE;
    }

    ze::Text textDefault("Hello world - default", &fontDefault, mode.height / 10);
    textDefault.setInternalColour(ze::Colour::Green);
    textDefault.centerText();
    ze::Text textSdf("Hello world - sdf", &fontSdf, mode.height / 10);
    textSdf.setInternalColour(ze::Colour::Cyan);
    textSdf.setExternalColour(ze::Colour::Blue);
    textSdf.setOutlineThickness(0.0f);
    textSdf.centerText();

    ze::VertexArray lines = ze::VertexArray(ze::DrawType::LineStrip, 5);
    auto updateGraphics = [&lines](int _w, int _h) {
        ze::Vector2f size((float)_w, (float)_h);

        lines[0] = ze::Vertex(ze::Vector2f(-size.x / 2.0f + 20.0f, -size.y / 2.0f + 20.0f), ze::Colour::Green);
        lines[1] = ze::Vertex(ze::Vector2f(-size.x / 2.0f + 20.0f, 0.0f), ze::Colour::Blue);
        lines[2] = ze::Vertex(ze::Vector2f(0.0f, 0.0f), ze::Colour::Red);
        lines[3] = ze::Vertex(ze::Vector2f(+size.x / 2.0f - 20.0f, 0.0f), ze::Colour::Blue);
        lines[4] = ze::Vertex(ze::Vector2f(+size.x / 2.0f - 20.0f, +size.y / 2.0f - 20.0f), ze::Colour::Green);

        lines.create();
    };

    updateGraphics(mode.width, mode.height);

    bool running = true;
    while (running) {

        ze::Event event;
        window.pumpEvents();
        while (window.pollEvent(event)) {
            if (event.type == ze::Event::EventType::WindowClosed) {
                running = false;
            }
            if (event.type == ze::Event::EventType::WindowSizeChanged) {
                updateGraphics(event.size.width, event.size.height);
            }
        }

        window.clear();

        size = ze::Vector2f(window.getSize());

        ze::RenderInfo info;
        info.projection = ze::Mat4x4::Orthographic3D(-size.x / 2.0f, +size.x / 2.0f, +size.y / 2.0f, -size.y / 2.0f, -1.0f, +1.0f);
        info.model.translate(ze::Vector3f(0.0f, size.y/4.0f, 0.0f));
        textDefault.render(window, info);
        info.model.translate(ze::Vector3f(0.0f, -size.y / 4.0f, 0.0f));
        lines.render(window, info);
        info.model.translate(ze::Vector3f(0.0f, -size.y / 4.0f, 0.0f));
        textSdf.render(window, info);

        window.display();
    }

    window.close();

    return EXIT_SUCCESS;
}