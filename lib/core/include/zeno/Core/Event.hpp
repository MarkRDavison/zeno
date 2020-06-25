#ifndef INCLUDED_ZENO_CORE_EVENT_HPP_
#define INCLUDED_ZENO_CORE_EVENT_HPP_

#include <cstdint>
#include <zeno/Core/Mouse.hpp>
#include <zeno/Core/Keyboard.hpp>

namespace ze {

    class Event {
    public:
        enum EventType {
            WindowClosed,
            GainedFocus,
            LostFocus,
            WindowSizeChanged,
            KeyDown,
            KeyRepeat,
            KeyUp,
            TextEntered,
            MouseWheelChanged,
            MouseButtonPressed,
            MouseButtonReleased,
            MouseMoved
        };

        enum ResizedType {
            Maximized,
            Minimized,
            Restored
        };

        struct KeyEvent {
            Keyboard::Key	key;
            bool			alt;
            bool			control;
            bool			shift;
            bool			system;
        };

        struct SizeEvent {
            unsigned int	width;
            unsigned int	height;
            ResizedType		type;
        };

        struct MouseWheelEvent {
            int				delta;
            int				x;
            int				y;
        };

        struct MouseButtonEvent {
            Mouse::Button	button;
            int				x;
            int				y;
        };

        struct PositionEvent {
            int				x;
            int				y;
        };

        struct TextEnteredEvent {
            uint32_t		character;
        };

        EventType		type;

        union {
            KeyEvent			key;
            SizeEvent			size;
            MouseWheelEvent		wheel;
            MouseButtonEvent	mouseButton;
            PositionEvent		position;
            TextEnteredEvent	text;
        };
    };

}

#endif // INCLUDED_ZENO_CORE_EVENT_HPP_