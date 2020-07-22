#include <zeno/Interaction/Transitions/TransitionType.hpp>

namespace ze {
	const TransitionType TransitionType::X_POS		= TransitionType(0.0f, [](Animator *_animator, float _value, bool _change) -> void {});
	const TransitionType TransitionType::Y_POS		= TransitionType(0.0f, [](Animator *_animator, float _value, bool _change) -> void {});
	const TransitionType TransitionType::WIDTH		= TransitionType(1.0f, [](Animator *_animator, float _value, bool _change) -> void {});
	const TransitionType TransitionType::HEIGHT		= TransitionType(1.0f, [](Animator *_animator, float _value, bool _change) -> void {});
	const TransitionType TransitionType::ALPHA		= TransitionType(1.0f, [](Animator *_animator, float _value, bool _change) -> void {});

	TransitionType::TransitionType(float _baseValue, ValueSetter _setter) :
		m_BaseValue(_baseValue),
		m_Setter(_setter) {

	}

	float TransitionType::getBaseValue() const {
		return m_BaseValue;
	}
	void TransitionType::applyValue(Animator* _animator, float _value, bool _change) const {
		m_Setter(_animator, _value, _change);
	}


	const TransitionType& TransitionType::getTransitionType(TransitionTypes _type) {
		switch (_type) {
		case TransitionTypes::X_POS:
			return X_POS;
		case TransitionTypes::Y_POS:
			return Y_POS;
		case TransitionTypes::WIDTH:
			return WIDTH;
		case TransitionTypes::HEIGHT:
			return HEIGHT;
		case TransitionTypes::ALPHA:
			return ALPHA;
		default:
			throw "Invalid Transition Types enum value";
		}
	}
}