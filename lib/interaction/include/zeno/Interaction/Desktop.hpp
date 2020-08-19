#ifndef INCLUDED_ZENO_INTERACTION_DESKTOP_HPP_
#define INCLUDED_ZENO_INTERACTION_DESKTOP_HPP_

#include <zeno/Core/Vector2.hpp>
#include <zeno/Graphics/Renderable.hpp>

#include <memory>

namespace ze {

	class Component;
	class Desktop : public ze::Renderable {
	public:
		Desktop(const ze::Window& _window);

		void initialise(const ze::Vector2f& _size);
		void notifyWindowSizeChanged(const ze::Vector2f& _size);

		void update(float _delta);
		bool handleEvent(const ze::Event& _event);
		void render(const ze::RenderTarget& _target, ze::RenderInfo _info) const override;

		ze::Vector2f getMousePositionRelative() const noexcept;
		ze::Vector2f getMousePositionPixel() const noexcept;

		ze::Vector2f getPixelSize() const;

		std::shared_ptr<Component> m_Root;

	private:
		ze::Vector2f size;
		const ze::Window& m_Window;
	};

}

#endif // INCLUDED_ZENO_INTERACTION_DESKTOP_HPP_