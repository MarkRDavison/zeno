#ifndef INCLUDED_ZENO_INTERACTION_TRANSITIONS_MODIFIER_HPP_
#define INCLUDED_ZENO_INTERACTION_TRANSITIONS_MODIFIER_HPP_

#include <zeno/Interaction/InteractionForward.hpp>
#include <zeno/Interaction/Transitions/TransitionTypes.hpp>
#include <zeno/Interaction/ValueDriver.hpp>
#include <memory>
#include <unordered_map>

namespace ze {

	using ValueDrivers = std::unordered_map<TransitionTypes, std::shared_ptr<ValueDriver>>;

	class Modifier {
	public:
		Modifier(ValueDrivers _drivers, bool _reverse, float _duration);

		void update(float _delta, Animator* _animator);

		bool hasFinishedTransition() const;
		bool isRedundant() const;
		float getCurrentValue(TransitionTypes _type) const;

	private:
		ValueDrivers m_ValueDrivers;
		bool m_Reverse;
		float m_Duration;
		float m_Time{ 0.0f };
	};

}

#endif // INCLUDED_ZENO_INTERACTION_TRANSITIONS_MODIFIER_HPP_