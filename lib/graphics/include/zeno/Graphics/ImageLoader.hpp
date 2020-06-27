#ifndef INCLUDED_ZENO_GRAPHICS_IMAGE_LOADER_HPP
#define INCLUDED_ZENO_GRAPHICS_IMAGE_LOADER_HPP

#include <string>
#include <vector>
#include <cstdint>

#include <zeno/Core/Vector2.hpp>

namespace ze {

    class ImageLoader {
    public:
        ImageLoader(void) = delete;
        ~ImageLoader(void) = delete;

        static bool loadImageFromFile(const std::string& _filename, std::vector<uint8_t>& _pixels, Vector2<unsigned int>& _size);
        static bool saveImageToFile(const std::string& _filename, const std::vector<uint8_t>& _pixels, const Vector2<unsigned int>& _size);

    };

}

#endif //~ INCLUDED_ZENO_GRAPHICS_IMAGE_LOADER_HPP