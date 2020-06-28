#include <zeno/Graphics/Text.hpp>
#include <GL/glew.h>
#include <cassert>

namespace ze {

	Text::Text() :
		Text(nullptr) {

	}
	Text::Text(Font* _font, unsigned _characterSize /*= 32*/) :
		Text("", _font, _characterSize) {

	}
	Text::Text(const std::string& _text, Font* _font, unsigned _characterSize /*= 32*/) :
		m_Font(_font),
		m_CharacterSize(_characterSize) {
		generateText(_text);
	}

	void Text::generateText(const std::string& _text) {
		m_Text = _text;
		regenerateText();
	}
	void Text::setFont(Font* _font) {
		m_Font = _font;
		regenerateText();
	}
	void Text::setCharacterSize(unsigned _characterSize) {
		m_CharacterSize = _characterSize;
		regenerateText();
	}
	void Text::setOutlineThickness(float _thickness) {
		m_Thickness = _thickness;
		if (m_Thickness < 0.0f) {
			m_Thickness = 0.0f;
		}
	}
	void Text::setInternalColour(const Colour& _colour) {
		m_InternalColour = _colour;
	}
	void Text::setExternalColour(const Colour& _colour) {
		m_ExternalColour = _colour;
	}

	void Text::render(const Window& _window, RenderInfo _info) const {
		if (m_Text.empty() || m_Font == nullptr) {
			return;
		}

		_info.texture = &m_Font->getTexture();
		_info.model *= Mat4x4::createRotationZ(getRotation());
		_info.model *= Mat4x4::createScale(Vector3f(getScale(), 0.0f));
		_info.model *= Mat4x4::createTranslation(Vector3f(getTranslation(), 0.0f));
		_info.model *= Mat4x4::createTranslation(Vector3f(getOrigin(), 0.0f));

		if (_info.texture != nullptr) {
			_info.texture->bind();
		}

		if (_info.shader == nullptr) {
			if (m_Font->type == Font::FontType::SignedDistanceField) {
				_info.shader = &Shader::SdfTextShader;
			} else {
				_info.shader = &Shader::TextShader;
			}
		}

		assert(_info.shader != nullptr);

		_info.shader->bind();

		if (m_Font->type == Font::FontType::SignedDistanceField) {
			_info.shader->passUniform("model", _info.model);
			_info.shader->passUniform("view", _info.view);
			_info.shader->passUniform("projection", _info.projection);
			_info.shader->passUniform("thickness", m_Thickness);
			_info.shader->passUniform("characterSize", static_cast<float>(m_CharacterSize));
			_info.shader->passUniform("internalColour", m_InternalColour);
			_info.shader->passUniform("externalColour", m_ExternalColour);
		} else {
			_info.shader->passUniform("model", _info.model);
			_info.shader->passUniform("view", _info.view);
			_info.shader->passUniform("projection", _info.projection);
			_info.shader->passUniform("colour", m_InternalColour);
		}

		glBindVertexArray(m_VertexArray.getVao());
		glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(m_VertexArray.size()));
		glBindVertexArray(0);

		if (_info.texture != nullptr) {
			ze::Texture::unbind();
		}
		if (_info.shader != nullptr) {
			ze::Shader::unbind();
		}
	}

	void Text::regenerateText() {
		m_VertexArray.clear();
		if (m_Font == nullptr || m_Text.empty()) {
			return;
		}

		m_Font->generateText(m_VertexArray, m_Text, m_CharacterSize);
	}

	void Text::centerText() {
		const auto& bounds = m_VertexArray.getBounds();
		setOrigin(ze::Vector2f{
			-(bounds.left + bounds.width) / 2.0f ,
			-(-bounds.bot / 2.0f + bounds.height) / 2.0f
			});
	}

	FloatRect Text::getBounds() const {
		auto bounds = m_VertexArray.getBounds();

		const auto& origin = getOrigin();
		const auto& translation = getTranslation();

		bounds.left += translation.x + origin.x;
		bounds.bot += translation.y + origin.y;

		return bounds;
	}

	std::string Text::getString() const {
		return m_Text;
	}
}