#ifndef INCLUDED_ZENO_GAME_FONT_MANAGER_HPP_
#define INCLUDED_ZENO_GAME_FONT_MANAGER_HPP_

#include <zeno/Graphics/Font.hpp>
#include <map>

namespace ze {

    class FontManager {
    public:
        bool loadFont(const std::string& _fontPath, const std::string& _fontName, unsigned int _generationSize);
        bool loadFontFiles(const std::string& _fontPath, const std::string& _fontName, unsigned int _generationSize, Font::FontType _type);
        bool createFont(const std::string& _fontName);
        Font& getFont(const std::string& _fontName);
        const Font& getFont(const std::string& _fontName) const;

    private:
        std::map<std::string, Font*> m_Fonts;
    };

}

#endif // INCLUDED_ZENO_GAME_FONT_MANAGER_HPP_