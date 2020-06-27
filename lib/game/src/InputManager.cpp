#include <zeno/Game/InputManager.hpp>
#include <zeno/Window/Window.hpp>

namespace ze {

	InputManager::InputManager(const ze::Window& _window) :
		m_Window(_window) {

	}
	InputManager::~InputManager() {

	}

	Vector2i InputManager::getMousePosition() const {
		return Mouse::getMousePosition(m_Window);
	}
	Vector2u InputManager::getWindowSize() const {
		return m_Window.getSize();
	}
	bool InputManager::isKeyDown(Keyboard::Key _key) {
		return Keyboard::isKeyPressed(_key, m_Window);
	}
	bool InputManager::isButtonDown(Mouse::Button _button) {
		return Mouse::isButtonPressed(_button, m_Window);
	}

}