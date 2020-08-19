#ifndef INCLUDED_ZENO_GRAPHICS_RENDER_WINDOW_HPP_
#define INCLUDED_ZENO_GRAPHICS_RENDER_WINDOW_HPP_

#include <zeno/Window/Window.hpp>
#include <zeno/Graphics/RenderTarget.hpp>

namespace ze {

	class RenderWindow : public Window, public RenderTarget {
	public:
		~RenderWindow() override = default;

		Vector2u getSize() const override;

		void clear() override;
		void clear(ze::Colour _colour) override;

		void setActive(bool _active) override;

		void display();
	};

}

#endif // INCLUDED_ZENO_GRAPHICS_RENDER_WINDOW_HPP_