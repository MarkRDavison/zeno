#ifndef INCLUDED_ZENO_WINDOW_WINDOW_HPP_
#define INCLUDED_ZENO_WINDOW_WINDOW_HPP_

#include <zeno/Core/Event.hpp>
#include <zeno/Window/VideoMode.hpp>
#include <queue>

struct GLFWwindow;
struct GLFWmonitor;

namespace ze {
    struct GLFWContext {
        GLFWContext();
        ~GLFWContext();

    private:
        static int instances;
    };

    class Window {
    public:
        Window();
        virtual ~Window();

        bool initialise(VideoMode _videoMode);

        void pumpEvents() const;
        bool pollEvent(Event& _event);

        void setVerticalSync(bool _vsync);
        void close();

        Vector2u getSize() const;
        void setSize(const Vector2u& _size) const;

        bool getWindowDecorated() const;
        void setWindowDecorated(bool _decorated);
        bool getWindowFullscreen() const;
        void setWindowFullscreen(bool _fullscreen);

        void center();

        GLFWwindow* getHandle() const { return m_Window; }

    private:
        static void mouseButtonCallback(GLFWwindow* _w, int _button, int _action, int _mods);
        static void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods);
        static void closeCallback(GLFWwindow* w);
        static void cursorPositionCallback(GLFWwindow* _w, double _x, double _y);
        static void windowSizeCallback(GLFWwindow* _w, int _width, int _height);
        static void windowFocusCallback(GLFWwindow* _w, int _focused);
        static void scrollCallback(GLFWwindow* _w, double _xoffset, double _yoffset);
        void centerWindow(GLFWwindow* _window, GLFWmonitor* _monitor);
        static void characterCallback(GLFWwindow* _window, unsigned _char);
    private:
        GLFWwindow* m_Window{ nullptr };

        std::queue<Event> m_Events;

        bool m_WindowDecorated{ true };
        bool m_Fullscreen{ false };
        bool m_VerticalSync{ true };
        ze::Vector2i m_WindowOffset;
    };

}

#endif // INCLUDED_ZENO_WINDOW_WINDOW_HPP_