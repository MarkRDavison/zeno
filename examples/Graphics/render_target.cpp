#include <zeno/Game.hpp>
#include <zeno/Graphics.hpp>
#include <cmath>
#include <chrono>
#include <thread>
#include <GL/glew.h>

class RenderTargetScene : public ze::Scene {
public:
    RenderTargetScene(
        ze::RenderWindow& _renderWindow,
        ze::RenderTexture& _renderTexture) 
    :
        renderWindow(_renderWindow),
        renderTexture(_renderTexture) {

    }
    ~RenderTargetScene() override = default;

    void update(float _delta) override {

    }

    bool handleEvent(const ze::Event& _event) override {
        if (_event.type == ze::Event::EventType::KeyDown) {
            if (_event.key.key == ze::Keyboard::Key::Space) {
                m_RenderToTexture = !m_RenderToTexture;
                if (m_RenderToTexture) {
                    std::cout << "Rendering to texture, and blitting to middle of screen" << std::endl;
                }
                else {
                    std::cout << "Rendering to window directly" << std::endl;
                }
            }
        }
        return false;
    }

    void render(const ze::RenderTarget& _target, ze::RenderInfo _info) const override {
        ze::RenderInfo info(_info);
        info.shader = &ze::Shader::VertexArrayShader;
        info.projection = ze::Mat4x4(1.0f);

        ze::VertexArray v(ze::DrawType::Triangles);

        v.appendVertex(ze::Vertex(ze::Vector2f(-1.0f, -1.0f), ze::Colour::Red));
        v.appendVertex(ze::Vertex(ze::Vector2f(+1.0f, -1.0f), ze::Colour::Green));
        v.appendVertex(ze::Vertex(ze::Vector2f(+1.0f, +1.0f), ze::Colour::Blue));
        v.appendVertex(ze::Vertex(ze::Vector2f(-1.0f, -1.0f), ze::Colour::Red));
        v.appendVertex(ze::Vertex(ze::Vector2f(+1.0f, +1.0f), ze::Colour::Blue));
        v.appendVertex(ze::Vertex(ze::Vector2f(-1.0f, +1.0f), ze::Colour::Yellow));

        v.create();

        if (m_RenderToTexture) {
            renderWindow.setActive(false);
            renderTexture.setActive(true);
            renderTexture.clear();
        }
        else {
            renderWindow.setActive(true);
            renderTexture.setActive(false);
            renderWindow.clear();
        }

        v.render(*(m_RenderToTexture 
            ? (ze::RenderTarget*) &renderTexture 
            : (ze::RenderTarget*) &renderWindow), info);

        if (m_RenderToTexture) {
            renderWindow.setActive(true);
            renderTexture.setActive(false);
            renderWindow.clear();

            ze::VertexArray blit(ze::DrawType::Triangles);

            blit.appendVertex(ze::Vertex(ze::Vector2f(-0.5f, -0.5f), ze::Colour::White, ze::Vector2f(0.0f, 0.0f)));
            blit.appendVertex(ze::Vertex(ze::Vector2f(+0.5f, -0.5f), ze::Colour::White, ze::Vector2f(1.0f, 0.0f)));
            blit.appendVertex(ze::Vertex(ze::Vector2f(+0.5f, +0.5f), ze::Colour::White, ze::Vector2f(1.0f, 1.0f)));
            blit.appendVertex(ze::Vertex(ze::Vector2f(-0.5f, -0.5f), ze::Colour::White, ze::Vector2f(0.0f, 0.0f)));
            blit.appendVertex(ze::Vertex(ze::Vector2f(+0.5f, +0.5f), ze::Colour::White, ze::Vector2f(1.0f, 1.0f)));
            blit.appendVertex(ze::Vertex(ze::Vector2f(-0.5f, +0.5f), ze::Colour::White, ze::Vector2f(0.0f, 1.0f)));

            blit.create();
            ze::RenderInfo blitInfo;
            blitInfo.shader = &ze::Shader::VertexArrayTextureShader;

            renderTexture.bindTexture();

            blit.render(renderWindow, blitInfo);

        }
    }

    ze::RenderWindow& renderWindow;
    ze::RenderTexture& renderTexture;
    bool m_RenderToTexture{ false };
};

int main(int _argc, char** _argv) {

    ze::Application app;
    if (!app.initialise(ze::VideoMode(640, 480, "Zeno Render Target"))) {
        return EXIT_FAILURE;
    }

    ze::RenderTexture renderTexture;
    if (!renderTexture.create(app.getWindow().getSize() * 2u)) {
        return EXIT_FAILURE;
    }

    renderTexture.setActive(false);

    RenderTargetScene scene(app.getWindow(), renderTexture);

    app.setScene(&scene);

    app.getWindow().setActive(true);

    app.start();

    return EXIT_SUCCESS;
}