#include <zeno/Graphics/Font.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <zeno/Graphics/Image.hpp>
#include <zeno/Graphics/Colour.hpp>
#include <algorithm>
#include <iostream>

#define MARGIN 2
#define DIST_MARGIN 4

#define ATLAS_WIDTH 1024
#define SEED_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()[]{}?><,./\\\"' :;~|-`=+_"

namespace ze {

    struct Point {
        Point() : Point(9999, 9999) {
        }
        Point(int _dx, int _dy) {
            dx = _dx;
            dy = _dy;
        }

        int dx, dy;

        int DistSq() const { return dx * dx + dy * dy; }
    };

    struct Grid {
        Grid(unsigned _width, unsigned _height, int _starting) :
            Width(_width),
            Height(_height) {
            grid = new Point * [_height];
            for (unsigned y = 0; y < _height; ++y) {
                grid[y] = new Point[_width];
                for (unsigned x = 0; x < _width; ++x) {
                    grid[y][x].dx = _starting;
                    grid[y][x].dy = _starting;
                }
            }
        }

        ~Grid() {
            for (unsigned y = 0; y < Height; ++y) {
                delete[] grid[y];
            }
            delete[] grid;
        }

        const unsigned Width;
        const unsigned Height;

        Point** grid;
    };

    Point inside = { 0, 0 };
    Point empty = { 9999, 9999 };

    Point Get(Grid& g, int x, int y) {
        // OPTIMIZATION: you can skip the edge check code if you make your grid 
        // have a 1-pixel gutter.
        if (x >= 0 && y >= 0 && x < static_cast<int>(g.Width) && y < static_cast<int>(g.Height))
            return g.grid[y][x];
        else
            return empty;
    }

    void Put(Grid& g, int x, int y, const Point& p) {
        g.grid[y][x] = p;
    }

    void Compare(Grid& g, Point& p, int x, int y, int offsetx, int offsety) {
        Point other = Get(g, x + offsetx, y + offsety);
        other.dx += offsetx;
        other.dy += offsety;

        if (other.DistSq() < p.DistSq())
            p = other;
    }

    void GenerateSDF(Grid& g) {
        // Pass 0
        for (int y = 0; y < static_cast<int>(g.Height); y++) {
            for (int x = 0; x < static_cast<int>(g.Width); x++) {
                Point p = Get(g, x, y);
                Compare(g, p, x, y, -1, 0);
                Compare(g, p, x, y, 0, -1);
                Compare(g, p, x, y, -1, -1);
                Compare(g, p, x, y, 1, -1);
                Put(g, x, y, p);
            }

            for (int x = static_cast<int>(g.Width) - 1; x >= 0; x--) {
                Point p = Get(g, x, y);
                Compare(g, p, x, y, 1, 0);
                Put(g, x, y, p);
            }
        }

        // Pass 1
        for (int y = static_cast<int>(g.Height) - 1; y >= 0; y--) {
            for (int x = static_cast<int>(g.Width) - 1; x >= 0; x--) {
                Point p = Get(g, x, y);
                Compare(g, p, x, y, 1, 0);
                Compare(g, p, x, y, 0, 1);
                Compare(g, p, x, y, -1, 1);
                Compare(g, p, x, y, 1, 1);
                Put(g, x, y, p);
            }

            for (int x = 0; x < static_cast<int>(g.Width); x++) {
                Point p = Get(g, x, y);
                Compare(g, p, x, y, -1, 0);
                Put(g, x, y, p);
            }
        }
    }


    Font::Font(FontType _type /*= FontType::Default*/) :
        m_GenerationSize(0),
        type(_type) {
        FT_Library lib;
        FT_Init_FreeType(&lib);
        m_Library = lib;
    }

    Font::Font(const std::string& _filename, unsigned _generationSize, FontType _type /*= FontType::Default*/) :
        type(_type) {
        FT_Library lib;
        FT_Init_FreeType(&lib);
        m_Library = lib;
        loadFromFile(_filename, _generationSize);
    }

    Font::~Font() {
        if (m_Loaded) {
            const FT_Library lib = static_cast<FT_Library>(m_Library);
            FT_Done_FreeType(lib);
        }
    }

    bool genChar(Image& _image, char _c, FT_Face _face) {
        const FT_UInt glyphIndex = FT_Get_Char_Index(_face, _c);
        const FT_Error loadGlyphError = FT_Load_Glyph(_face, glyphIndex, FT_LOAD_RENDER);
        if (loadGlyphError != 0) {
            // Failed to load glyph
            return false;
        }

        const FT_GlyphSlot glyph = _face->glyph;

        Grid grid1(glyph->bitmap.width + 2 * DIST_MARGIN, glyph->bitmap.rows + 2 * DIST_MARGIN, 0);
        Grid grid2(glyph->bitmap.width + 2 * DIST_MARGIN, glyph->bitmap.rows + 2 * DIST_MARGIN, 9999);
        for (int y = 0; y < static_cast<int>(glyph->bitmap.rows); y++) {
            for (int x = 0; x < static_cast<int>(glyph->bitmap.width); x++) {
                // TODO: Put a border around the generated image when atlassing ...
                if (y >= static_cast<int>(glyph->bitmap.rows) || x >= static_cast<int>(glyph->bitmap.width)) {
                    Put(grid2, x + DIST_MARGIN, y + DIST_MARGIN, inside);
                    Put(grid1, x + DIST_MARGIN, y + DIST_MARGIN, empty);
                } else {
                    const float value = static_cast<float>(glyph->bitmap.buffer[y * glyph->bitmap.width + x]) / 255.0f;

                    // Points inside get marked with a dx/dy of zero.
                    // Points outside get marked with an infinitely large distance.
                    if (value < 0.5f) {
                        Put(grid1, x + DIST_MARGIN, y + DIST_MARGIN, inside);
                        Put(grid2, x + DIST_MARGIN, y + DIST_MARGIN, empty);
                    } else {
                        Put(grid2, x + DIST_MARGIN, y + DIST_MARGIN, inside);
                        Put(grid1, x + DIST_MARGIN, y + DIST_MARGIN, empty);
                    }
                }
            }
        }

        GenerateSDF(grid1);
        GenerateSDF(grid2);

        _image.create(grid1.Width, grid1.Height);

        for (int y = 0; y < static_cast<int>(grid1.Height); y++) {
            for (int x = 0; x < static_cast<int>(grid1.Width); x++) {
                // Calculate the actual distance from the dx/dy
                const int dist1 = static_cast<int>(sqrt(static_cast<double>(Get(grid1, x, y).DistSq())));
                const int dist2 = static_cast<int>(sqrt(static_cast<double>(Get(grid2, x, y).DistSq())));
                const int dist = dist1 - dist2;

                // Clamp and scale it.
                int c = dist * 3 + 128;
                if (c < 0) c = 0;
                if (c > 255) c = 255;

                _image.setPixel(x, y, ze::Colour(static_cast<float>(c) / 255.0f, 0.0f, 0.0f));
            }
        }

        return true;
    }

    bool Font::loadFontFile(const std::string& _filename, unsigned _generationSize, FontType _type /*= FontType::Default*/) {
        m_GlyphData.clear();
        m_Loaded = false;
        m_GenerationSize = _generationSize;
        type = _type;

        if (type == FontType::SignedDistanceField) {
            return loadFromFileSDF(_filename, _generationSize);
        }

        return loadFromFileDefault(_filename, _generationSize);
    }
    bool Font::createFont() {
        if (!m_Texture.loadFromImage(m_Image)) {
            std::cerr << "Failed to create font atlas texture from image" << std::endl;
            return false;
        }
        m_Loaded = true;
        return true;
    }
    bool Font::loadFromFile(const std::string& _filename, unsigned _generationSize, FontType _type /*= FontType::Default*/) {
        if (!loadFontFile(_filename, _generationSize, _type)) {
            return false;
        }

        return createFont();
    }

    const ze::Texture& Font::getTexture() const {
        return m_Texture;
    }

    void Font::generateText(ze::VertexArray& _vertexArray, const std::string& _text, unsigned _characterSize) {
        _vertexArray = ze::VertexArray(_text.size() * 6);

        ze::Vector2f penPosition{};
        const ze::Vector2u textureSize = m_Texture.getSize();
        const float charSize = static_cast<float>(_characterSize);
        const float ratio = charSize / static_cast<float>(m_GenerationSize);

        for (unsigned i = 0; i < _text.size(); ++i) {
            const char _c = _text[i];

            if (_c == ' ') {
                penPosition.x += charSize * ratio * 0.25f;
                continue;
            }

            if (m_GlyphData.count(_c) == 0) {
                std::cerr << "Cannot use character '" << _c << "' in text." << std::endl;
                continue;
            }

            const Glyph& g = m_GlyphData[_c];

            // Kerning, rise etc
            const ze::Vector2f charOffset{ 0.0f,  static_cast<float>(g.bearingY >> 6) - static_cast<float>(g.h) };

            _vertexArray[i * 6 + 0] = ze::Vertex{ ze::Vector3f{
                penPosition.x + (charOffset.x) * ratio,
                penPosition.y + (charOffset.y) * ratio,
                0.0f
            }, ze::Colour::White, ze::Vector2f{
                static_cast<float>(g.x) / textureSize.x,
                1.0f - (static_cast<float>(g.y + g.h) / textureSize.y)
            } };
            _vertexArray[i * 6 + 1] = ze::Vertex{ ze::Vector3f{
                penPosition.x + (charOffset.x + g.w) * ratio,
                penPosition.y + (charOffset.y) * ratio,
                0.0f
            }, ze::Colour::White, ze::Vector2f{
                static_cast<float>(g.x + g.w) / textureSize.x,
                1.0f - (static_cast<float>(g.y + g.h) / textureSize.y)
            } };
            _vertexArray[i * 6 + 2] = ze::Vertex{ ze::Vector3f{
                penPosition.x + (charOffset.x + g.w) * ratio,
                penPosition.y + (charOffset.y + g.h) * ratio,
                0.0f
            }, ze::Colour::White, ze::Vector2f{
                static_cast<float>(g.x + g.w) / textureSize.x,
                1.0f - (static_cast<float>(g.y) / textureSize.y)
            } };


            _vertexArray[i * 6 + 3] = ze::Vertex{ ze::Vector3f{
                penPosition.x + (charOffset.x) * ratio,
                penPosition.y + (charOffset.y) * ratio,
                0.0f
            }, ze::Colour::White, ze::Vector2f{
                static_cast<float>(g.x) / textureSize.x,
                1.0f - (static_cast<float>(g.y + g.h) / textureSize.y)
            } };
            _vertexArray[i * 6 + 4] = ze::Vertex{ ze::Vector3f{
                penPosition.x + (charOffset.x + g.w) * ratio,
                penPosition.y + (charOffset.y + g.h) * ratio,
                0.0f
            }, ze::Colour::White, ze::Vector2f{
                static_cast<float>(g.x + g.w) / textureSize.x,
                1.0f - (static_cast<float>(g.y) / textureSize.y)
            } };
            _vertexArray[i * 6 + 5] = ze::Vertex{ ze::Vector3f{
                penPosition.x + (charOffset.x) * ratio,
                penPosition.y + (charOffset.y + g.h) * ratio,
                0.0f
            }, ze::Colour::White, ze::Vector2f{
                static_cast<float>(g.x) / textureSize.x,
                1.0f - (static_cast<float>(g.y) / textureSize.y)
            } };

            penPosition.x += static_cast<float>(g.w) * ratio;
        }

        _vertexArray.create();
    }

    bool Font::loadFromFileSDF(const std::string& _filename, unsigned _generationSize) {
        const FT_Library lib = static_cast<FT_Library>(m_Library);
        FT_Face face;

        const FT_Error newFaceError = FT_New_Face(lib, _filename.c_str(), 0, &face);
        if (newFaceError != 0) {
            // Failed to create font face
            return false;
        }

        const FT_Error setPixelError = FT_Set_Pixel_Sizes(face, 0, m_GenerationSize);
        if (setPixelError != 0) {
            // Failed to set pixel size
            return false;
        }

        m_Image.create(ATLAS_WIDTH, ATLAS_WIDTH);

        const std::string chars = SEED_CHARS;

        unsigned currentX = 0;
        unsigned currentY = 0;
        unsigned nextY = 0;

        for (unsigned i = 0; i < chars.size(); ++i) {
            const char c = chars[i];

            ze::Image image;
            if (!genChar(image, c, face)) {
                std::cerr << "Failed to load character '" << c << "'" << std::endl;
                continue;

            }

            if (currentX + image.getSize().x + 2 * MARGIN >= m_Image.getSize().x) {
                // Need to go to next row
                currentX = 0;
                currentY = nextY;
                if (currentY + image.getSize().y + 2 * MARGIN >= m_Image.getSize().y) {
                    m_Image.expandVertically(m_Image.getSize().y);
                }
            }

            for (unsigned y = 0; y < image.getSize().y; ++y) {
                for (unsigned x = 0; x < image.getSize().x; ++x) {
                    m_Image.setPixel(currentX + x + MARGIN, currentY + y + MARGIN, image.getPixel(x, y));
                }
            }

            const auto v1 = face->glyph->metrics.height >> 6;
            const auto v2 = face->glyph->metrics.horiBearingY >> 6;

            Glyph g;
            g.c = c;
            g.x = currentX + MARGIN;
            g.y = currentY + MARGIN;
            g.w = image.getSize().x;
            g.h = image.getSize().y;
            g.yOff = static_cast<float>(v2) - static_cast<float>(v1);
            g.top = face->glyph->bitmap_top;
            g.left = face->glyph->bitmap_left;
            g.bearingY = face->glyph->metrics.horiBearingY;
            g.advanceY = face->glyph->metrics.vertAdvance;
            g.heightRatio = static_cast<float>(g.h) / static_cast<float>(m_GenerationSize);
            g.widthRatio = static_cast<float>(g.w) / static_cast<float>(m_GenerationSize);
            m_GlyphData[c] = g;


            nextY = std::max(currentY + image.getSize().y + 2 * MARGIN, nextY);
            currentX += image.getSize().x + 2 * MARGIN;
        }

        return true;
    }

    bool genCharNonSDF(Image& _image, char _c, FT_Face _face) {
        const FT_UInt glyphIndex = FT_Get_Char_Index(_face, _c);
        const FT_Error loadGlyphError = FT_Load_Glyph(_face, glyphIndex, FT_LOAD_RENDER);
        if (loadGlyphError != 0) {
            // Failed to load glyph
            return false;
        }

        const FT_GlyphSlot glyph = _face->glyph;

        _image.create(glyph->bitmap.width + 2 * DIST_MARGIN, glyph->bitmap.rows + 2 * DIST_MARGIN, ze::Colour::Transparent);

        for (int y = 0; y < static_cast<int>(glyph->bitmap.rows); y++) {
            for (int x = 0; x < static_cast<int>(glyph->bitmap.width); x++) {
                if (y >= static_cast<int>(glyph->bitmap.rows) || x >= static_cast<int>(glyph->bitmap.width)) {
                    continue;
                }

                const float value = static_cast<float>(glyph->bitmap.buffer[y * glyph->bitmap.width + x]) / 255.0f;

                _image.setPixel(x + DIST_MARGIN, y + DIST_MARGIN, ze::Colour(value, 0.0f, 0.0f, 1.0f));
            }
        }

        return true;
    }

    bool Font::loadFromFileDefault(const std::string& _filename, unsigned _generationSize) {
        const FT_Library lib = static_cast<FT_Library>(m_Library);
        FT_Face face;

        const FT_Error newFaceError = FT_New_Face(lib, _filename.c_str(), 0, &face);
        if (newFaceError != 0) {
            // Failed to create font face
            return false;
        }

        const FT_Error setPixelError = FT_Set_Pixel_Sizes(face, 0, m_GenerationSize);
        if (setPixelError != 0) {
            // Failed to set pixel size
            return false;
        }

        m_Image.create(ATLAS_WIDTH, ATLAS_WIDTH);

        const std::string chars = SEED_CHARS;

        unsigned currentX = 0;
        unsigned currentY = 0;
        unsigned nextY = 0;

        for (unsigned i = 0; i < chars.size(); ++i) {
            const char c = chars[i];

            ze::Image image;
            if (!genCharNonSDF(image, c, face)) {
                std::cerr << "Failed to load character '" << c << "'" << std::endl;
                continue;

            }

            if (currentX + image.getSize().x + 2 * MARGIN >= m_Image.getSize().x) {
                // Need to go to next row
                currentX = 0;
                currentY = nextY;
                if (currentY + image.getSize().y + 2 * MARGIN >= m_Image.getSize().y) {
                    m_Image.expandVertically(m_Image.getSize().y);
                }
            }

            for (unsigned y = 0; y < image.getSize().y; ++y) {
                for (unsigned x = 0; x < image.getSize().x; ++x) {
                    m_Image.setPixel(currentX + x + MARGIN, currentY + y + MARGIN, image.getPixel(x, y));
                }
            }

            const auto v1 = face->glyph->metrics.height >> 6;
            const auto v2 = face->glyph->metrics.horiBearingY >> 6;

            Glyph g;
            g.c = c;
            g.x = currentX + MARGIN;
            g.y = currentY + MARGIN;
            g.w = image.getSize().x;
            g.h = image.getSize().y;
            g.yOff = static_cast<float>(v2) - static_cast<float>(v1);
            g.top = face->glyph->bitmap_top;
            g.left = face->glyph->bitmap_left;
            g.bearingY = face->glyph->metrics.horiBearingY;
            g.advanceY = face->glyph->metrics.vertAdvance;
            g.heightRatio = static_cast<float>(g.h) / static_cast<float>(m_GenerationSize);
            g.widthRatio = static_cast<float>(g.w) / static_cast<float>(m_GenerationSize);
            m_GlyphData[c] = g;

            nextY = std::max(currentY + image.getSize().y + 2 * MARGIN, nextY);
            currentX += image.getSize().x + 2 * MARGIN;
        }

        return true;
    }
}
