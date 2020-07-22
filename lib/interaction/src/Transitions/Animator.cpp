#include <zeno/Interaction/Transitions/Animator.hpp>
#include <zeno/Interaction/Transitions/Modifier.hpp>
#include <zeno/Interaction/Transitions/Transition.hpp>
#include <zeno/Interaction/Component.hpp>
#include <algorithm>

namespace ze {

	Animator::Animator(std::shared_ptr<Component> _component) :
		m_Component(_component) {
		resetValues();
	}

	void Animator::resetValues() {
		m_X = 0.0f;
		m_Y = 0.0f;
		m_Width = 1.0f;
		m_Height = 1.0f;
		m_Alpha = 1.0f;
	}

	float Animator::getX() const { return m_X; }
	float Animator::getY() const { return m_Y; }
	float Animator::getWidth() const { return m_Width; }
	float Animator::getHeight() const { return m_Height; }
	float Animator::getAlpha() const { return m_Alpha; }

	void Animator::applyX(float _x, bool _change) {
		m_X = _x;
		m_PositionChange |= _change;
	}
	void Animator::applyY(float _y, bool _change) {
		m_Y = _y;
		m_PositionChange |= _change;
	}
	void Animator::applyWidth(float _width, bool _change) {
		m_Width *= _width;
		m_PositionChange |= _change;
		m_ScaleChange |= _change;
	}
	void Animator::applyHeight(float _height, bool _change) {
		m_Height *= _height;
		m_PositionChange |= _change;
		m_ScaleChange |= _change;
	}
	void Animator::applyAlpha(float _alpha, bool _change) {
		m_Alpha *= _alpha;
		m_AlphaChange |= _change;
	}

	void Animator::applyModdifiers(std::shared_ptr<Transition> _transition, bool _reverse, float _delay) {
		const auto id = _transition->getId();		
		m_Modifiers[id] = _transition->createModifier(m_Modifiers[id], _reverse, _delay);
	}
	bool Animator::isDoingTransition(TransitionId _transitionId) const {
		if (m_Modifiers.count(_transitionId) > 0) {
			return !m_Modifiers.at(_transitionId)->hasFinishedTransition();
		}
		return false;
	}

	void Animator::update(float _delta) {
		if (m_Modifiers.empty()) { return; }

		resetValues();
		bool redundantModifiers = false;
		for (auto& [k, v] : m_Modifiers) {
			v->update(_delta, this);
			if (v->isRedundant()) {
				redundantModifiers = true;
			}
		}

		if (redundantModifiers) {
			for (auto it = m_Modifiers.begin(); it != m_Modifiers.end();) {
				if (it->second->isRedundant()) {
					it = m_Modifiers.erase(it);
				} else {
					++it;
				}
			}
		}

		updateComponentAsNecessary();
	}
	void Animator::updateComponentAsNecessary() const {
		if (m_PositionChange) {
			m_Component->notifyDimensionChange();
		}

		if (m_AlphaChange) {
			m_Component->updateTotalAlpha();
		}
	}

}