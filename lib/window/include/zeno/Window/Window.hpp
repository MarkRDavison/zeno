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
        ~Window();

        bool initialise(VideoMode _videoMode);

        void pumpEvents() const;
        bool pollEvent(Event& _event);
        static void clear();
        void display() const;
        void close();

        void setVerticalSync(bool _vsync);

        Vector2u getSize() const;
        void setSize(const Vector2u& _size) const;

        void centerCurrentWindow();

        GLFWwindow* getHandle() const { return m_Window; }

    private:
        static void mouseButtonCallback(GLFWwindow* _w, int _button, int _action, int _mods);
        static void keyCallback(GLFWwindow* w, int key, int scancode, int action, int mods);
        static void closeCallback(GLFWwindow* w);
        static void cursorPositionCallback(GLFWwindow* _w, double _x, double _y);
        static void windowSizeCallback(GLFWwindow* _w, int _width, int _height);
        static void windowFocusCallback(GLFWwindow* _w, int _focused);
        static void scrollCallback(GLFWwindow* _w, double _xoffset, double _yoffset);
        static void centerWindow(GLFWwindow* _window, GLFWmonitor* _monitor);
        static void characterCallback(GLFWwindow* _window, unsigned _char);
    private:
        GLFWwindow* m_Window{ nullptr };

        std::queue<Event> m_Events;
    };

}

#endif // INCLUDED_ZENO_WINDOW_WINDOW_HPP_