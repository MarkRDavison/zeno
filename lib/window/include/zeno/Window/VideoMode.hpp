#ifndef INCLUDED_ZENO_WINDOW_VIDEO_MODE_HPP_
#define INCLUDED_ZENO_WINDOW_VIDEO_MODE_HPP_

#include <zeno/Core/Vector2.hpp>
#include <string>

namespace ze {

    class VideoMode {
    public:
        VideoMode();
        VideoMode(unsigned _width, unsigned _height, const std::string& _title);
        VideoMode(unsigned _width, unsigned _height, const std::string& _title, int _decoration);
        explicit VideoMode(const Vector2u& _size, const std::string& _title);

        unsigned width;
        unsigned height;

        int decoration;

        bool fullscreen{ false };

        std::string title;

        unsigned contextMajor{ 3 };
        unsigned contextMinor{ 3 };
    };

}

#endif // INCLUDED_ZENO_WINDOW_VIDEO_MODE_HPP_