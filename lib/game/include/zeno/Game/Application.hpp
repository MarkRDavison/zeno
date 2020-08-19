#ifndef INCLUDED_ZENO_GAME_APPLICATION_HPP_
#define INCLUDED_ZENO_GAME_APPLICATION_HPP_

#include <zeno/Core/Vector2.hpp>
#include <zeno/Game/Scene.hpp>
#include <zeno/Graphics/RenderWindow.hpp>

namespace ze {

    class Application {
    public:
        Application() = default;
        Application(const Application & _other) = delete;
        Application(Application && _other) noexcept = delete;
        Application& operator=(const Application & _other) = delete;
        Application& operator=(Application && _other) noexcept = delete;

        bool initialise(const Vector2u& _resolution, const std::string& _name);
        bool initialise(const VideoMode& _videoMode);
        void start();
        void stop();

        bool startSplash(const VideoMode& _videoMode, Scene* _splashScene);
        void renderSplash();
        bool splashFinished();
        bool splashFinished(const VideoMode& _videoMode);

        void setScene(Scene* _scene);

        RenderWindow& getWindow();
        const RenderWindow& getWindow() const;

    private:
        void update(float _delta);
        void render(RenderTarget& _target, float _alpha);

    private:
        GLFWContext context{};
        bool m_Running{ false };
        bool m_Initialised{ false };
        bool m_SplashShowing{ false };
        VideoMode m_StartingMode;

        RenderWindow m_Window;
        Scene* m_Scene{ nullptr };
    };

}

#endif // INCLUDED_ZENO_GAME_APPLICATION_HPP_