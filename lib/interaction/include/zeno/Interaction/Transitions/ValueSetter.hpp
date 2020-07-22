#ifndef INCLUDED_ZENO_INTERACTION_TRANSITIONS_VALUE_SETTER_HPP_
#define INCLUDED_ZENO_INTERACTION_TRANSITIONS_VALUE_SETTER_HPP_

#include <zeno/Interaction/InteractionForward.hpp>
#include <functional>
#include <memory>

namespace ze {

	using ValueSetter = std::function<void(Animator* _animator, float _value, bool _change)>;

}

#endif // INCLUDED_ZENO_INTERACTION_TRANSITIONS_VALUE_SETTER_HPP_