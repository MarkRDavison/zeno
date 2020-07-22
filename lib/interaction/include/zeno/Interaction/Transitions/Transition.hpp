#ifndef INCLUDED_ZENO_INTERACTION_TRANSITIONS_TRANSITION_HPP_
#define INCLUDED_ZENO_INTERACTION_TRANSITIONS_TRANSITION_HPP_

#include <zeno/Interaction/InteractionForward.hpp>
#include <zeno/Interaction/Transitions/TransitionTypes.hpp>
#include <unordered_map>
#include <memory>
#include <string>

namespace ze {

	using TransitionId = std::string;
	using ValueTransitions = std::unordered_map<TransitionTypes, std::shared_ptr<ValueTransition>>;

	class Transition {
	public:
		Transition(TransitionId _id);

		Transition& add(TransitionTypes _type, std::shared_ptr<ValueTransition> _transition);

		std::shared_ptr<Modifier> createModifier(
			std::shared_ptr<Modifier> _oldModifier, 
			bool _reverse, 
			float _delay);

		std::shared_ptr<ValueDriver> initialiseDriver(
			TransitionTypes _type,
			std::shared_ptr<ValueTransition> _transition,
			std::shared_ptr<Modifier> _oldModifier,
			bool _reverse,
			float _delay);

		TransitionId getId() const { return m_Id; }

	private:
		TransitionId m_Id;
		ValueTransitions m_ValueTransitions;
		float m_Duration{ 0.0f };
	};

}

#endif // INCLUDED_ZENO_INTERACTION_TRANSITIONS_TRANSITION_HPP_