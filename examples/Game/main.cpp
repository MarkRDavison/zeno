#include <zeno/Game.hpp>
#include <zeno/Graphics.hpp>
#include <cmath>

class ExampleScene : public ze::Scene {
public:
    ~ExampleScene() override = default;

    void update(float _delta) override {
        m_Time += _delta;
    }
    bool handleEvent(const ze::Event& _event) override {
        return false;
    }
    void render(const ze::Window& _window, ze::RenderInfo _info) const override {
        ze::RenderInfo info(_info);
        const ze::Vector2f size(_window.getSize());
        info.projection = ze::Mat4x4::Orthographic3D(-size.x / 2.0f, +size.x / 2.0f, +size.y / 2.0f, -size.y / 2.0f, -1.0f, +1.0f);

        ze::CircleShape c(64.0f);
        c.setInternalColour(ze::Colour::Green);
        c.setOutlineColour(ze::Colour::Magenta);
        c.setOutlineThickness(8.0f);

        info.model.translate(ze::Vector3f(0.0f, 4.0f * sinf(m_Time) * 180.0f / 3.14159265f, 0.0f));

        c.render(_window, info);
    }

    float m_Time{ 0.0f };
};

int main(int _argc, char** _argv) {
    ze::VideoMode mode = ze::VideoMode(800, 600, "Zeno Game");
    ze::Application app;

    if (!app.initialise(mode)) {
        return EXIT_FAILURE;
    }

    ExampleScene scene;

    app.setScene(&scene);

    app.start();

    return EXIT_SUCCESS;
}