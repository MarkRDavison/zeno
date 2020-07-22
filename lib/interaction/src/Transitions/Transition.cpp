#include <zeno/Interaction/Transitions/Transition.hpp>
#include <zeno/Interaction/Transitions/TransitionType.hpp>
#include <zeno/Interaction/Transitions/Modifier.hpp>
#include <zeno/Interaction/Transitions/ValueTransition.hpp>
#include <zeno/Interaction/ValueDriver.hpp>
#include <algorithm>

namespace ze {


	Transition::Transition(TransitionId _id) :
		m_Id(_id){ }
	Transition& Transition::add(TransitionTypes _type, std::shared_ptr<ValueTransition> _transition) {
		m_ValueTransitions[_type] = _transition;
		m_Duration = std::max(m_Duration, _transition->getDuration());
		return *this;
	}

	std::shared_ptr<Modifier> Transition::createModifier(
		std::shared_ptr<Modifier> _oldModifier,
		bool _reverse,
		float _delay) {

		const float transitionDuration = m_Duration + _delay;
		ValueDrivers driverInstances;
		for (const auto& [k, v] : m_ValueTransitions) {
			driverInstances[k] = initialiseDriver(k, v, _oldModifier, _reverse, _delay);
		}

		return std::make_shared<Modifier>(driverInstances, _reverse, transitionDuration);
	}

	std::shared_ptr<ValueDriver> Transition::initialiseDriver(
		TransitionTypes _type,
		std::shared_ptr<ValueTransition> _transition,
		std::shared_ptr<Modifier> _oldModifier,
		bool _reverse,
		float _delay) {

		const auto& transitionType = TransitionType::getTransitionType(_type);
		const float baseValue = transitionType.getBaseValue();
		const float currValue = 
			_oldModifier 
			? _oldModifier->getCurrentValue(_type)
			: (_reverse
				? _transition->getHiddenValue()
				: baseValue);

		return _transition->initDriver(baseValue, currValue, _reverse, _delay, m_Duration);
	}
}