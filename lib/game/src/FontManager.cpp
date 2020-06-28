#include <zeno/Game/FontManager.hpp>

namespace ze {

	bool FontManager::loadFont(const std::string& _fontPath, const std::string& _fontName, unsigned int _generationSize) {
		Font* font = new Font();
		if (font->loadFromFile(_fontPath, _generationSize)) {
			m_Fonts[_fontName] = font;
			return true;
		}
		delete font;
		return false;
	}
	bool FontManager::loadFontFiles(const std::string& _fontPath, const std::string& _fontName, unsigned int _generationSize, Font::FontType _type) {
		Font* font = new Font(_type);
		if (font->loadFontFile(_fontPath, _generationSize)) {
			m_Fonts[_fontName] = font;
			return true;
		}
		return false;
	}
	bool FontManager::createFont(const std::string& _fontName) {
		auto& t = getFont(_fontName);
		return t.createFont();
	}
	Font& FontManager::getFont(const std::string& _fontName) {
		return *(*m_Fonts.find(_fontName)).second;
	}
	const Font& FontManager::getFont(const std::string& _fontName) const {
		return *(*m_Fonts.find(_fontName)).second;
	}
}
