#include <zeno/Window/Window.hpp>
#include <zeno/Window/VideoMode.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <future>
#include <cmath>

namespace ze {

    int GLFWContext::instances{ 0 };

    Window::Window() {

    }

    Window::~Window() {
        if (m_Window != nullptr) {
            close();
        }
    }

    void Window::mouseButtonCallback(GLFWwindow* _w, int _button, int _action, int _mods) {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(_w));
        Event e{};
        e.type = (_action == GLFW_PRESS
            ? Event::EventType::MouseButtonPressed
            : Event::EventType::MouseButtonReleased);

        const Vector2i position = Mouse::getMousePosition(*window);
        e.mouseButton.button = _button == GLFW_MOUSE_BUTTON_1
            ? Mouse::Button::Left
            : (_button == GLFW_MOUSE_BUTTON_2
                ? Mouse::Button::Right
                : Mouse::Button::Middle);
        e.mouseButton.x = position.x;
        e.mouseButton.y = position.y;

        window->m_Events.push(e);
    }

    void Window::keyCallback(GLFWwindow* w, int _key, int _scancode, int _action, int _mods) {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(w));

        Event e{};
        e.key.key = Keyboard::glfwToZenoKey(_key);
        e.key.shift = _mods & GLFW_MOD_SHIFT;
        e.key.alt = _mods & GLFW_MOD_ALT;
        e.key.control = _mods & GLFW_MOD_CONTROL;
        e.key.system = _mods & GLFW_MOD_SUPER;
        e.type = _action == GLFW_PRESS
            ? Event::EventType::KeyDown
            : _action == GLFW_REPEAT
            ? Event::EventType::KeyRepeat
            : Event::EventType::KeyUp;

        window->m_Events.push(e);
    }

    void Window::closeCallback(GLFWwindow* w) {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(w));
        Event e{};
        e.type = Event::EventType::WindowClosed;
        window->m_Events.push(e);
    }

    void Window::cursorPositionCallback(GLFWwindow* _w, double _x, double _y) {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(_w));
        Event e{};
        e.type = Event::EventType::MouseMoved;
        e.position.x = static_cast<int>(std::floor(_x));
        e.position.y = static_cast<int>(std::floor(_y));
        window->m_Events.push(e);
    }

    void Window::windowSizeCallback(GLFWwindow* _w, int _width, int _height) {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(_w));
        Event e{};
        e.type = Event::EventType::WindowSizeChanged;
        e.size.type = Event::Restored;
        e.size.width = _width;
        e.size.height = _height;
        window->m_Events.push(e);
    }

    void Window::windowFocusCallback(GLFWwindow* _w, int _focused) {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(_w));
        Event e{};
        e.type = _focused != 0
            ? Event::EventType::GainedFocus
            : Event::EventType::LostFocus;
        window->m_Events.push(e);
    }

    void Window::scrollCallback(GLFWwindow* _w, double _xoffset, double _yoffset) {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(_w));
        Event e{};
        e.type = Event::EventType::MouseWheelChanged;
        const Vector2i position = Mouse::getMousePosition(*window);
        e.wheel.x = position.x;
        e.wheel.y = position.y;
        e.wheel.delta = static_cast<int>(_yoffset);
        window->m_Events.push(e);
    }

    void Window::characterCallback(GLFWwindow* _window, unsigned _char) {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(_window));
        Event e{};
        e.type = Event::EventType::TextEntered;
        e.text.character = _char;
        window->m_Events.push(e);
    }

    bool Window::initialise(VideoMode _videoMode) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _videoMode.contextMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _videoMode.contextMinor);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_DECORATED, _videoMode.decoration);

        if (m_Window != nullptr) {
            close();
        }

        if (_videoMode.fullscreen) {
            auto monitor = glfwGetPrimaryMonitor();
            auto mode = glfwGetVideoMode(monitor);
            m_Window = glfwCreateWindow(mode->width, mode->height, _videoMode.title.c_str(), monitor, nullptr);
        } else {
            m_Window = glfwCreateWindow(_videoMode.width, _videoMode.height, _videoMode.title.c_str(), nullptr, nullptr);
        }

        glfwSetWindowUserPointer(m_Window, this);
        glfwMakeContextCurrent(m_Window);
        setVerticalSync(false);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glewExperimental = true;
        const GLenum err = glewInit();
        if (err != GLEW_OK) {
            std::cerr << "Failed to initialise Glew: " << glewGetErrorString(err) << std::endl;
            return false;
        }

        glfwSetKeyCallback(m_Window, keyCallback);
        glfwSetWindowCloseCallback(m_Window, closeCallback);
        glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);
        glfwSetCursorPosCallback(m_Window, cursorPositionCallback);
        glfwSetWindowSizeCallback(m_Window, windowSizeCallback);
        glfwSetWindowFocusCallback(m_Window, windowFocusCallback);
        glfwSetScrollCallback(m_Window, scrollCallback);
        glfwSetCharCallback(m_Window, characterCallback);

        centerCurrentWindow();

        return true;
    }

    void Window::setVerticalSync(bool _vsync) {
        glfwSwapInterval(_vsync ? 1 : 0);
    }

    void Window::dumpSystemInfo() {
        int CPUInfo[4] = { -1 };
        char CPUBrandString[0x40];
        // Get the information associated with each extended ID.
        __cpuid(CPUInfo, 0x80000000);
        const unsigned nExIds = CPUInfo[0];
        for (unsigned i = 0x80000000; i <= nExIds; ++i) {
            __cpuid(CPUInfo, i);
            // Interpret CPU brand string
            if (i == 0x80000002)
                memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
            else if (i == 0x80000003)
                memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
            else if (i == 0x80000004)
                memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
        }

        std::cout << "CPU          : " << CPUBrandString << std::endl;
        std::cout << "GLFW version : " << glfwGetVersionString() << std::endl;
        std::cout << "GLEW_VERSION : " << glewGetString(GLEW_VERSION) << std::endl;
        std::cout << "GL_VERSION   : " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GL_VENDOR    : " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "GL_RENDERER  : " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "GLSL_VERSION : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    }

    void Window::pumpEvents() const {
        glfwPollEvents();
    }

    bool Window::pollEvent(Event& _event) {
        if (!m_Events.empty()) {
            _event = m_Events.front();
            m_Events.pop();
            return true;
        }
        return false;
    }

    void Window::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::display() const {
        glfwSwapBuffers(m_Window);
    }

    void Window::close() {
        if (m_Window != nullptr) {
            glfwDestroyWindow(m_Window);
            m_Window = nullptr;
        }
    }

    Vector2u Window::getSize() const {
        Vector2i size;
        glfwGetWindowSize(m_Window, &size.x, &size.y);
        return Vector2u(size);
    }

    void Window::setSize(const Vector2u& _size) const {
        glfwSetWindowSize(m_Window, static_cast<int>(_size.x), static_cast<int>(_size.y));
    }

    void Window::centerCurrentWindow() {
        GLFWmonitor* primary = glfwGetPrimaryMonitor();
        centerWindow(m_Window, primary);
    }
    void Window::centerWindow(GLFWwindow* _window, GLFWmonitor* _monitor) {
        if (!_monitor) {
            return;
        }

        const GLFWvidmode* mode = glfwGetVideoMode(_monitor);
        if (!mode) {
            return;
        }

        int monitorX, monitorY;
        glfwGetMonitorPos(_monitor, &monitorX, &monitorY);

        int windowWidth, windowHeight;
        glfwGetWindowSize(_window, &windowWidth, &windowHeight);

        glfwSetWindowPos(_window,
            monitorX + (mode->width - windowWidth) / 2,
            monitorY + (mode->height - windowHeight) / 2);
    }

    GLFWContext::GLFWContext() {
        if (instances == 0) {
            glfwInit();
        }
        instances++;
    }
    GLFWContext::~GLFWContext() {
        instances--;
        if (instances == 0) {
            glfwTerminate();
        }
    }


}
