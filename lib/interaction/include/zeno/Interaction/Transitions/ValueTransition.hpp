#ifndef INCLUDED_ZENO_INTERACTION_TRANSITIONS_VALUE_TRANSITION_HPP_
#define INCLUDED_ZENO_INTERACTION_TRANSITIONS_VALUE_TRANSITION_HPP_

#include <zeno/Interaction/InteractionForward.hpp>
#include <memory>

namespace ze {

	class ValueTransition {
	public:
		virtual ~ValueTransition() = 0;

		virtual float getHiddenValue() = 0;
		virtual std::shared_ptr<ValueDriver> initDriver(
			float _baseValue, 
			float _currentValue,
			bool _reverse,
			float _delay,
			float _totalDuration) = 0;
		virtual float getDuration() = 0;
	};

	inline ValueTransition::~ValueTransition() = default;
}

#endif // INCLUDED_ZENO_INTERACTION_TRANSITIONS_VALUE_TRANSITION_HPP_