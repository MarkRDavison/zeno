#ifndef INCLUDED_ZENO_INTERACTION_CONTROLS_BUTTON_CONTROL_HPP_
#define INCLUDED_ZENO_INTERACTION_CONTROLS_BUTTON_CONTROL_HPP_

#include <zeno/Interaction/Controls/ClickableControl.hpp>
#include <zeno/Core/Signal.hpp>

namespace ze {

	class ButtonControl : public ClickableControl {
	public:
		~ButtonControl() override = default;
		void update(float _delta) override;
		bool onClick(ze::Mouse::Button _button) override;
		void renderComponent(const ze::RenderTarget& _target, ze::RenderInfo _info) const override;

		ze::Signal<ze::Mouse::Button> clickSignal;
		ze::Colour defaultColour;
		ze::Colour hoverColour;
	};

}

#endif // INCLUDED_ZENO_INTERACTION_CONTROLS_BUTTON_CONTROL_HPP_