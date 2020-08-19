#include <zeno/Graphics/Texture.hpp>
#include <zeno/Graphics/Image.hpp>
#include <GL/glew.h>

namespace ze {

	static const int wrapModes[3] = { GL_CLAMP_TO_EDGE, GL_REPEAT, GL_MIRRORED_REPEAT };

	Texture::Texture(void) :
		m_TextureHandle(0),
		m_XAxisWrap(TextureWrap::REPEAT),
		m_YAxisWrap(TextureWrap::REPEAT) {
	}

	Texture::~Texture(void) {
		// TODO: STOP LEAKING
	}


	bool Texture::loadFromFile(const std::string& _filename) {
		if (!loadTexture(_filename)) {
			return false;
		}

		return createTexture();
	}
	bool Texture::loadFromImage(const Image& _image) {
		m_Loaded = false;
		m_Image.create(_image.getSize().x, _image.getSize().y);
		m_Image.copy(_image);
		return createTexture();
	}
	bool Texture::loadTexture(const std::string& _filename) {
		m_Loaded = false;
		return m_Image.loadFromFile(_filename);
	}
	bool Texture::createTexture() {
		//~ Deletes the texture if it exists
		glDeleteTextures(1, &m_TextureHandle);

		// TODO: Maybe we need to flip?????? Seems silly
		//~ Flips around y-axis as opengl origin is bottom left
	/*	for (unsigned int y = 0; y < m_Image.getSize().y; y += 1) {
			for (unsigned int x = 0; x < m_Image.getSize().x; x += 1) {
				const Colour col = m_Image.getPixel(x, _image.getSize().y - y - 1);

				m_PixelData.at((y * _image.getSize().x + x) * 4 + 0) = static_cast<uint8_t>(255.0f * col.r);
				m_PixelData.at((y * _image.getSize().x + x) * 4 + 1) = static_cast<uint8_t>(255.0f * col.g);
				m_PixelData.at((y * _image.getSize().x + x) * 4 + 2) = static_cast<uint8_t>(255.0f * col.b);
				m_PixelData.at((y * _image.getSize().x + x) * 4 + 3) = static_cast<uint8_t>(255.0f * col.a);
			}
		}*/

		Image flipped;
		flipped.create(m_Image.getSize().x, m_Image.getSize().y);

		for (unsigned int y = 0; y < m_Image.getSize().y; y += 1) {
			for (unsigned int x = 0; x < m_Image.getSize().x; x += 1) {
				const Colour col = m_Image.getPixel(x, m_Image.getSize().y - y - 1);
				flipped.setPixel(x, y, col);
			}
		}

		m_Size = m_Image.getSize();

		glGenTextures(1, &m_TextureHandle);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TextureHandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Size.x, m_Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, flipped.getPixelPointer());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModes[(unsigned)m_XAxisWrap]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModes[(unsigned)m_YAxisWrap]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		m_Loaded = true;
		return true;
	}

	void Texture::bind(void) const {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TextureHandle);
		glUniform1i(m_TextureHandle, 0);
	}
	void Texture::unbind(void) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Vector2u Texture::getSize(void) const {
		return m_Size;
	}

	void Texture::setWrapMode(TextureWrap _xAxis, TextureWrap _yAxis) {
		m_XAxisWrap = _xAxis;
		m_YAxisWrap = _yAxis;

		bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModes[(unsigned)m_XAxisWrap]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModes[(unsigned)m_YAxisWrap]);

		unbind();
	}
	bool Texture::isLoaded() const {
		return m_Loaded;
	}

}