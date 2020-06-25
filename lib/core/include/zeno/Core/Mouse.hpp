#ifndef INCLUDED_ZENO_CORE_MOUSE_HPP_
#define INCLUDED_ZENO_CORE_MOUSE_HPP_

#include <zeno/Core/Vector2.hpp>

namespace ze {
    class Window;
    class Mouse {
    public:
        Mouse() = delete;
        ~Mouse() = delete;

        enum class Button {
            Left,
            Right,
            Middle,
            Extra1,
            Extra2,

            NUM_BUTTONS
        };

        static bool isButtonPressed(Button _button, const Window& _window);
        static Vector2i getMousePosition(const Window& _window);

        static int zenoToGlfwButton(Button _button);
        static Button glfwToZenoButton(int _button);
    };
}

#endif // INCLUDED_ZENO_CORE_MOUSE_HPP_