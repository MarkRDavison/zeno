#ifndef INCLUDED_ZENO_GAME_INPUT_ACTION_HPP_
#define INCLUDED_ZENO_GAME_INPUT_ACTION_HPP_

#include <zeno/Core/Keyboard.hpp>
#include <zeno/Core/Mouse.hpp>

namespace ze {

	struct InputAction {
		enum class InputActivationType {
			KeyPress,
			KeyHold,
			MouseButtonPress,
			MouseButtonHold,
			None
		};


		InputActivationType primaryActivationType{ InputActivationType::None };
		ze::Keyboard::Key primaryKey{ ze::Keyboard::Key::Unknown };
		ze::Mouse::Button primaryButton{ ze::Mouse::Button::NUM_BUTTONS };

		InputActivationType secondaryActivationType{ InputActivationType::None };
		ze::Keyboard::Key secondaryKey{ ze::Keyboard::Key::Unknown };
		ze::Mouse::Button secondaryButton{ ze::Mouse::Button::NUM_BUTTONS };

		// If secondary required to activate requires both otherwise requires either
		bool secondaryRequired{ false };
		bool allowRepeat{ false };

		bool modifierControl{ false };
		bool modifierAlt{ false };
		bool modifierShift{ false };
	};

}

#endif // INCLUDED_ZENO_GAME_INPUT_ACTION_HPP_