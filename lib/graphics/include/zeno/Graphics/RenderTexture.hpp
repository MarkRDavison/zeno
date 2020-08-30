#ifndef INCLUDED_ZENO_GRAPHICS_RENDER_TEXTURE_HPP_
#define INCLUDED_ZENO_GRAPHICS_RENDER_TEXTURE_HPP_

#include <zeno/Graphics/RenderTarget.hpp>

namespace ze {

	class RenderTexture : public RenderTarget {
	public:
		~RenderTexture() override;

		Vector2u getSize() const override;

		bool create(const Vector2u& _size);

		void clear() override;
		void clear(ze::Colour _colour) override;

		void setActive(bool _active) override;

		void bindTexture() const;

		unsigned m_Framebuffer{ 0 };
		unsigned m_DepthBuffer{ 0 };
		unsigned m_Texture{ 0 };
		unsigned m_DepthTexture{ 0 };
		ze::Vector2u m_Size;
	};

}

#endif // INCLUDED_ZENO_GRAPHICS_RENDER_TEXTURE_HPP_