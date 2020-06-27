#ifndef INCLUDED_ZENO_GAME_INPUT_MANAGER_HPP_
#define INCLUDED_ZENO_GAME_INPUT_MANAGER_HPP_

#include <zeno/Core/Mat4x4.hpp>
#include <zeno/Core/Vector2.hpp>
#include <zeno/Core/Keyboard.hpp>
#include <zeno/Core/Mouse.hpp>
#include <zeno/Core/Event.hpp>

namespace ze {

	class IInputManager {
	public:
		virtual ~IInputManager() = 0;
		virtual Vector2i getMousePosition() const = 0;
		virtual Vector2u getWindowSize() const = 0;
		virtual bool isKeyDown(ze::Keyboard::Key _key) = 0;
		virtual bool isButtonDown(ze::Mouse::Button _button) = 0;

	};

	class InputManager : public IInputManager {
	public:
		InputManager(const ze::Window& _window);
		~InputManager() override;

		Vector2i getMousePosition() const override;
		Vector2u getWindowSize() const override;
		bool isKeyDown(ze::Keyboard::Key _key) override;
		bool isButtonDown(ze::Mouse::Button _button) override;


	private:
		const ze::Window& m_Window;
	};

	inline IInputManager::~IInputManager() = default;
}

#endif // INCLUDED_ZENO_GAME_INPUT_MANAGER_HPP_