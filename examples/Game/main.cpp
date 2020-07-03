#include <zeno/Game.hpp>
#include <zeno/Graphics.hpp>
#include <cmath>
#include <chrono>
#include <thread>

class SplashScene : public ze::Scene {
public:
    ~SplashScene() override = default;

    void update(float _delta) override {

    }
    bool handleEvent(const ze::Event & _event) override {
        return false;
    }
    void render(const ze::Window & _window, ze::RenderInfo _info) const override {
        ze::RenderInfo info(_info);
        const ze::Vector2f size(_window.getSize());
        info.projection = ze::Mat4x4::Orthographic3D(-size.x / 2.0f, +size.x / 2.0f, +size.y / 2.0f, -size.y / 2.0f, -1.0f, +1.0f);

        ze::CircleShape c(96.0f);
        c.setInternalColour(ze::Colour::Yellow);
        c.setOutlineColour(ze::Colour::Red);
        c.setOutlineThickness(8.0f);

        c.render(_window, info);

        const float margin = 4.0f;
        const float barSize = 32.0f;
        const float barLength = size.x - barSize;

        ze::RectangleShape progress = ze::RectangleShape(ze::Vector2f(barLength, barSize), ze::Vector2f(-barLength / 2.0f, -size.y / 2.0f + barSize  / 2.0f));

        progress.setInternalColour(ze::Colour::Blue);
        progress.render(_window, info);
        progress.setSize(ze::Vector2f(barLength * m_Percentage / 100.0f - margin * 2.0f, progress.getBounds().height - margin * 2.0f));
        progress.translate(ze::Vector2f(margin, margin));
        progress.setInternalColour(ze::Colour::Green);
        progress.render(_window, info);
    }

    float m_Percentage{ 0.0f };
};

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

        info.model.translate(ze::Vector3f(0.0f, size.y / 150.f * sinf(m_Time) * 180.0f / 3.14159265f, 0.0f));

        c.render(_window, info);
    }

    float m_Time{ 0.0f };
};

int main(int _argc, char** _argv) {
    ze::Application app;

    SplashScene splashScene;

    if (!app.startSplash(ze::VideoMode(), &splashScene)) {
        return EXIT_FAILURE;
    }

    // Start doing stuff
    std::this_thread::sleep_for(std::chrono::seconds(1));
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    // Do stuff
    std::this_thread::sleep_for(std::chrono::seconds(1));
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    // Do stuff
    std::this_thread::sleep_for(std::chrono::seconds(1));
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    // Do stuff
    std::this_thread::sleep_for(std::chrono::seconds(1));
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    // Do stuff
    std::this_thread::sleep_for(std::chrono::seconds(1));
    splashScene.m_Percentage += 20.0f;
    app.renderSplash();

    // Finish doing stuff
    std::this_thread::sleep_for(std::chrono::seconds(1));
    if (!app.splashFinished(ze::VideoMode(1280, 720, "Zeno Game"))) {
        return EXIT_FAILURE;
    }

    ExampleScene scene;

    app.setScene(&scene);

    app.start();

    return EXIT_SUCCESS;
}