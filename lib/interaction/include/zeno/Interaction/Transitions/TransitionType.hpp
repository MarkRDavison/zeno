#ifndef INCLUDED_ZENO_INTERACTION_TRANSITIONS_TRANSITION_TYPE_HPP_
#define INCLUDED_ZENO_INTERACTION_TRANSITIONS_TRANSITION_TYPE_HPP_

#include <zeno/Interaction/Transitions/ValueSetter.hpp>
#include <zeno/Interaction/Transitions/TransitionTypes.hpp>

namespace ze {

	class TransitionType {
		TransitionType(float _baseValue, ValueSetter _setter);
	public:

		float getBaseValue() const;
		void applyValue(Animator* _animator, float _value, bool _change) const;

		const static TransitionType X_POS;
		const static TransitionType Y_POS;
		const static TransitionType WIDTH;
		const static TransitionType HEIGHT;
		const static TransitionType ALPHA;

		static const TransitionType& getTransitionType(TransitionTypes _type);

	private:
		float m_BaseValue;
		ValueSetter m_Setter;
	};

}

#endif // INCLUDED_ZENO_INTERACTION_TRANSITIONS_TRANSITION_TYPE_HPP_