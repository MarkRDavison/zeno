#ifndef INCLUDED_ZENO_GRAPHICS_IMAGE_HPP
#define INCLUDED_ZENO_GRAPHICS_IMAGE_HPP

#include <string>
#include <cstdint>
#include <vector>

#include <zeno/Core/Vector2.hpp>
#include <zeno/Graphics/Colour.hpp>

namespace ze {

    class Image {
    public:
        void create(unsigned int _width, unsigned int _height, const Colour& _colour = Colour::Black);

        bool loadFromFile(const std::string& _filename);
        bool saveToFile(const std::string& _filename) const;

        Vector2<unsigned int> getSize(void) const;

        Colour getPixel(unsigned int _x, unsigned int _y) const;
        void setPixel(unsigned int _x, unsigned int _y, const Colour& _colour);

        const uint8_t* getPixelPointer(void) const;
        void copy(const Image& _image, const Vector2u& _offset = Vector2u());

        void expandVertically(unsigned int _increaseSize, const Colour& _colour = Colour::Black);

    private:
        Vector2<unsigned int>			m_Size;
        std::vector<uint8_t>			m_Pixels;

    };

}

#endif //~ INCLUDED_ZENO_GRAPHICS_IMAGE_HPP