#ifndef INCLUDED_ZENO_GRAPHICS_FONT_HPP_
#define INCLUDED_ZENO_GRAPHICS_FONT_HPP_

#include <map>
#include <string>
#include <zeno/Graphics/Texture.hpp>
#include <zeno/Graphics/VertexArray.hpp>

namespace ze {

    struct Glyph {
        char c;
        unsigned x;
        unsigned y;
        unsigned w;
        unsigned h;

        unsigned top;
        unsigned left;

        unsigned bearingY;
        unsigned advanceY;

        float heightRatio;
        float widthRatio;

        float yOff;
    };

    class Font {
    public:

        enum class FontType {
            SignedDistanceField,
            Default
        };

        Font(FontType _type = FontType::Default);
        Font(const std::string& _filename, unsigned _generationSize, FontType _type = FontType::Default);
        ~Font();

        bool loadFromFile(const std::string& _filename, unsigned _generationSize, FontType _type = FontType::Default);

        bool loadFontFile(const std::string& _filename, unsigned _generationSize, FontType _type = FontType::Default);
        bool createFont();

        void generateText(ze::VertexArray& _vertexArray, const std::string& _text, unsigned _characterSize);

        const ze::Texture& getTexture() const;
        FontType type;

    protected:
        bool loadFromFileSDF(const std::string& _filename, unsigned _generationSize);
        bool loadFromFileDefault(const std::string& _filename, unsigned _generationSize);

    private:
        bool m_Loaded{ false };
        void* m_Library{ nullptr };

        ze::Image m_Image{};
        ze::Texture m_Texture{};

        unsigned m_GenerationSize;

        std::map<char, Glyph> m_GlyphData;
    };

}

#endif // INCLUDED_ZENO_GRAPHICS_FONT_HPP_