#ifndef INCLUDED_ZENO_GRAPHICS_TEXTURE_HPP
#define INCLUDED_ZENO_GRAPHICS_TEXTURE_HPP

#include <zeno/Core/Vector2.hpp>
#include <zeno/Graphics/Image.hpp>
#include <vector>
#include <string>
#include <cstdint>

namespace ze {

	class Texture {
	public:
		enum class TextureWrap {
			CLAMP,
			REPEAT,
			MIRRORED_REPEAT
		};

		Texture(void);
		~Texture(void);

		bool loadFromFile(const std::string& _filename);
		bool loadFromImage(const Image& _image);
		bool loadTexture(const std::string& _filename);
		bool createTexture();

		void bind(void) const;
		static void unbind(void);

		Vector2u getSize(void) const;

		void setWrapMode(TextureWrap _xAxis, TextureWrap _yAxis);

		bool isLoaded() const;

	private:
		bool m_Loaded{ false };
		unsigned int 				m_TextureHandle;

		Vector2u					m_Size;
		Image						m_Image;
		TextureWrap					m_XAxisWrap;
		TextureWrap					m_YAxisWrap;
	};

}

#endif //~ INCLUDED_ZENO_GRAPHICS_TEXTURE_HPP