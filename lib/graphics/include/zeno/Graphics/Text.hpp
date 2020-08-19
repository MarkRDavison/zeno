#ifndef INCLUDED_ZENO_GRAPHICS_TEXT_HPP_
#define INCLUDED_ZENO_GRAPHICS_TEXT_HPP_

#include <zeno/Graphics/Font.hpp>
#include <zeno/Graphics/VertexArray.hpp>
#include <zeno/Core/Transformable2D.hpp>

namespace ze {

	class Text : public Renderable, public Transformable2D {
	public:

		Text();
		Text(Font* _font, unsigned _characterSize = 32);
		Text(const std::string& _text, Font* _font, unsigned _characterSize = 32);

		void generateText(const std::string& _text);
		void setFont(Font* _font);
		void setCharacterSize(unsigned _characterSize);
		void setOutlineThickness(float _thickness);
		void setInternalColour(const Colour& _colour);
		void setExternalColour(const Colour& _colour);

		void render(const RenderTarget& _target, RenderInfo _info) const override;
		void centerText();

		std::string getString() const;
		unsigned getCharacterSize() const {
			return m_CharacterSize;
		}

		FloatRect getBounds() const;

	protected:
		void regenerateText();

	private:
		std::string m_Text;
		Font* m_Font;
		unsigned m_CharacterSize;
		float m_Thickness{ 0.0f };
		ze::Colour m_InternalColour{ ze::Colour::White };
		ze::Colour m_ExternalColour{ ze::Colour::Transparent };

		ze::VertexArray m_VertexArray;
	};

}

#endif // INCLUDED_ZENO_GRAPHICS_TEXT_HPP_