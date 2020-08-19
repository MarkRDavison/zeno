#include <zeno/Interaction/Desktop.hpp>
#include <zeno/Interaction/Component.hpp>
#include <zeno/Interaction/Controls/BlockControl.hpp>
#include <zeno/Graphics.hpp>

namespace ze {

	Desktop::Desktop(const ze::Window& _window) :
		m_Window(_window) {

	}
	void Desktop::initialise(const ze::Vector2f& _size) {
		m_Root = std::make_shared<BlockControl>();
		((BlockControl*)m_Root.get())->colour = ze::Colour::Transparent;
		m_Root->forceInitialisation(ze::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
		m_Root->desktop = this;
		m_Root->level = 1;
		m_Root->parent = m_Root;
		size = _size;
	}
	void Desktop::notifyWindowSizeChanged(const ze::Vector2f& _size) {
		size = _size;
		if (m_Root->reloadOnSizeChange) {
			m_Root->reset();
			m_Root->initialise();
		}
		else {
			m_Root->notifyDimensionChange();
		}
	}

	void Desktop::update(float _delta){
		m_Root->update(_delta);
	}
	bool Desktop::handleEvent(const ze::Event& _event) {
		if (m_Root->handleEvent(_event)) {
			return true;
		}

		return false;
	}
	void Desktop::render(const ze::RenderTarget& _target, ze::RenderInfo _info) const {
		ze::RenderInfo info(_info);
		info.projection = ze::Mat4x4::Orthographic3D(0.0f, 1.0f, 1.0f, 0.0f, 10.0f, 0.0f);

		m_Root->render(_target, info);
	}

	ze::Vector2f Desktop::getMousePositionRelative() const noexcept {
		const ze::Vector2f size(m_Window.getSize());
		const ze::Vector2f pos = ze::Vector2f(ze::Mouse::getMousePosition(m_Window));
		return ze::Vector2f(pos.x / size.x, (size.y - pos.y) / size.y);
	}
	ze::Vector2f Desktop::getMousePositionPixel() const noexcept {
		const ze::Vector2f size(m_Window.getSize());
		const ze::Vector2f pos = ze::Vector2f(ze::Mouse::getMousePosition(m_Window));
		return ze::Vector2f(pos.x, size.y - pos.y);
	}

	ze::Vector2f Desktop::getPixelSize() const {
		return size;
	}
}