#include <zeno/Core/Mouse.hpp>
#include <zeno/Window/Window.hpp>
#include <GLFW/glfw3.h>
#include <cmath>

namespace ze {

    bool Mouse::isButtonPressed(Button _button, const Window& _window) {
        return glfwGetMouseButton(static_cast<GLFWwindow*>(_window.getHandle()), zenoToGlfwButton(_button)) == GLFW_PRESS;
    }

    Vector2i Mouse::getMousePosition(const Window& _window) {
        double xpos, ypos;
        glfwGetCursorPos(_window.getHandle(), &xpos, &ypos);
        return { static_cast<int>(std::floor(xpos)), static_cast<int>(std::floor(ypos)) };
    }

    int Mouse::zenoToGlfwButton(Button _button) {
        switch (_button) {
        case Button::Left:      return GLFW_MOUSE_BUTTON_1;
        case Button::Right:     return GLFW_MOUSE_BUTTON_2;
        case Button::Middle:    return GLFW_MOUSE_BUTTON_3;
        case Button::Extra1:    return GLFW_MOUSE_BUTTON_4;
        case Button::Extra2:    return GLFW_MOUSE_BUTTON_5;
        case Button::NUM_BUTTONS:
        default:                return GLFW_MOUSE_BUTTON_LAST;
        }
    }
    Mouse::Button Mouse::glfwToZenoButton(int _button) {
        switch (_button) {
        case GLFW_MOUSE_BUTTON_1:        return Button::Left;
        case GLFW_MOUSE_BUTTON_2:        return Button::Right;
        case GLFW_MOUSE_BUTTON_3:        return Button::Middle;
        case GLFW_MOUSE_BUTTON_4:        return Button::Extra1;
        case GLFW_MOUSE_BUTTON_5:        return Button::Extra2;
        default:                         return Button::NUM_BUTTONS;
        }
    }
}
