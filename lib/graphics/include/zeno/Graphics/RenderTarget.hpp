#ifndef INCLUDED_ZENO_GRAPHICS_RENDER_TARGET_HPP_
#define INCLUDED_ZENO_GRAPHICS_RENDER_TARGET_HPP_

#include <zeno/Core/Vector2.hpp>
#include <zeno/Graphics/Colour.hpp>

namespace ze {

	class RenderTarget {
	public:
		virtual ~RenderTarget() = default;

		virtual void clear() = 0;
		virtual void clear(ze::Colour _colour) = 0;

		virtual void setActive(bool _active) = 0;

		virtual Vector2u getSize() const = 0;

	protected:
		bool m_Active{ false };
	};

}

#endif // INCLUDED_ZENO_GRAPHICS_RENDER_TARGET_HPP_