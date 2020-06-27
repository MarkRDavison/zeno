#include <zeno/Graphics/ImageLoader.hpp>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace ze {

    bool ImageLoader::loadImageFromFile(const std::string& _filename, std::vector<uint8_t>& _pixels, Vector2<unsigned int>& _size) {
        _pixels.clear();

        int width, height, channels;
        unsigned char* ptr = stbi_load(_filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

        if (ptr && width && height) {
            _size.x = static_cast<unsigned int>(width);
            _size.y = static_cast<unsigned int>(height);

            _pixels.resize(width * height * 4);
            memcpy(&_pixels[0], ptr, _pixels.size());

            stbi_image_free(ptr);
            _pixels.resize(width * height * 4);

            return true;
        }

        std::cerr << "Failed to load image '" << _filename << "', error: " << stbi_failure_reason() << std::endl;
        return false;
    }

    bool ImageLoader::saveImageToFile(const std::string& _filename, const std::vector<uint8_t>& _pixels, const Vector2<unsigned int>& _size) {
        if (!_pixels.empty() && _size.x > 0 && _size.y > 0) {
            if (_filename.size() > 3) {
                const std::string extension = _filename.substr(_filename.size() - 3);
                if (extension == "bmp") {
                    if (stbi_write_bmp(_filename.c_str(), _size.x, _size.y, 4, &_pixels[0])) {
                        return true;
                    }
                } else if (extension == "tga") {
                    if (stbi_write_tga(_filename.c_str(), _size.x, _size.y, 4, &_pixels[0])) {
                        return true;
                    }
                } else if (extension == "png") {
                    if (stbi_write_png(_filename.c_str(), _size.x, _size.y, 4, &_pixels[0], 0)) {
                        return true;
                    }
                }
            }
        }

        std::cerr << "Failed to save image: '" << _filename << "'" << std::endl;
        return false;
    }

}