#include <zeno/Interaction/Controls/ClickableControl.hpp>
#include <zeno/Interaction/Desktop.hpp>
#include <iostream>

namespace ze {

	void ClickableControl::update(float _delta) {
		updateMouseOver();

		Component::update(_delta);
	}
	bool ClickableControl::handleEvent(const ze::Event& _event) {
		if (_event.type == ze::Event::EventType::MouseButtonPressed) {
			if (m_MouseOver) {
				if (onClick(_event.mouseButton.button)) {
					return true;
				}
			}
		}
		return false;
	}

	void ClickableControl::updateMouseOver()  {
		m_MouseOver = false;
		const ze::Vector2f mouse = desktop->getMousePositionRelative();

		if (x <= mouse.x && mouse.x <= x + width &&
			y <= mouse.y && mouse.y <= y + height) {
			m_MouseOver = true;
			return;
		}
	}
}