#ifndef INCLUDED_ZENO_INTERACTION_CONTROLS_CLICKABLE_CONTROL_HPP_
#define INCLUDED_ZENO_INTERACTION_CONTROLS_CLICKABLE_CONTROL_HPP_

#include <zeno/Interaction/Component.hpp>

namespace ze {

	class ClickableControl : public Component {
	public:
		virtual ~ClickableControl() = 0;
		
		void update(float _delta) override;
		bool handleEvent(const ze::Event& _event) override;

		virtual bool onClick(ze::Mouse::Button _button) = 0;

		void updateMouseOver() ;

	protected:
		bool m_MouseOver;
	};

	inline ClickableControl::~ClickableControl() = default;
}

#endif // INCLUDED_ZENO_INTERACTION_CONTROLS_CLICKABLE_CONTROL_HPP_