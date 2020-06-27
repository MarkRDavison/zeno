#ifndef INCLUDED_ZENO_GAME_INPUT_ACTION_MANAGER_HPP_
#define INCLUDED_ZENO_GAME_INPUT_ACTION_MANAGER_HPP_

#include <zeno/Game/InputAction.hpp>
#include <unordered_map>
#include <unordered_set>

namespace ze {

	class Event;
	class IInputManager;

	class IInputActionManager {
	public:
		virtual ~IInputActionManager() = 0;

		virtual void registerAction(const std::string& _key, const InputAction& _action) = 0;
		virtual void updateCachedInputs() = 0;

		virtual bool isActionInvoked(const std::string& _key) const = 0;
	};

	class InputActionManager : public IInputActionManager {
	public:
		InputActionManager(IInputManager& _inputManager);
		~InputActionManager() override = default;

		void registerAction(const std::string& _key, const InputAction& _action) override;
		void updateCachedInputs() override;

		bool isActionInvoked(const std::string& _key) const override;
		bool isActionInvoked(const InputAction& _action) const;

	private:
		IInputManager& m_InputManager;
		std::unordered_map<std::string, InputAction> registeredActions;
		std::unordered_map<Mouse::Button, bool> cachedButtons;
		std::unordered_map<Keyboard::Key, bool> cachedKeys;
	};

	inline IInputActionManager::~IInputActionManager() = default;
}

#endif // INCLUDED_ZENO_GAME_INPUT_ACTION_MANAGER_HPP_