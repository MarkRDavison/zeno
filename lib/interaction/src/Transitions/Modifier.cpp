#include <zeno/Interaction/Transitions/Modifier.hpp>
#include <zeno/Interaction/Transitions/Animator.hpp>
#include <zeno/Interaction/Transitions/TransitionType.hpp>

namespace ze {

	Modifier::Modifier(ValueDrivers _drivers, bool _reverse, float _duration) :
		m_ValueDrivers(_drivers),
		m_Reverse(_reverse),
		m_Duration(_duration) {

	}

	void Modifier::update(float _delta, Animator *_animator) {
		const bool valueChanging = !hasFinishedTransition();
		m_Time += _delta;

		for (const auto& [k, v] : m_ValueDrivers) {
			const float value = v->update(_delta);
		
			TransitionType::getTransitionType(k).applyValue(_animator, value, valueChanging);
		}
	}

	bool Modifier::hasFinishedTransition() const { 
		return m_Time > m_Duration;
	}
	bool Modifier::isRedundant() const {
		return m_Reverse && hasFinishedTransition();
	}
	float Modifier::getCurrentValue(TransitionTypes _type) const {
		const auto& driver = m_ValueDrivers.at(_type);
		return driver->getCurrentValue();
	}

}