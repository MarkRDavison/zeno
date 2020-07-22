#ifndef INCLUDED_ZENO_INTERACTION_CONSTRAINT_SET_HPP_
#define INCLUDED_ZENO_INTERACTION_CONSTRAINT_SET_HPP_

#include <zeno/Interaction/InteractionForward.hpp>
#include <memory>

namespace ze {

	class ConstraintSet {
	public:

		ConstraintSet();
		ConstraintSet(
			std::shared_ptr<Constraint> _xConstraint,
			std::shared_ptr<Constraint> _yConstraint,
			std::shared_ptr<Constraint> _widthConstraint,
			std::shared_ptr<Constraint> _heightConstraint);

		void notify(std::shared_ptr<Component> _current, std::shared_ptr<Component> _parent);

		std::shared_ptr<Constraint> xConstraint;
		std::shared_ptr<Constraint> yConstraint;
		std::shared_ptr<Constraint> widthConstraint;
		std::shared_ptr<Constraint> heightConstraint;
	};


}

#endif // INCLUDED_ZENO_INTERACTION_CONSTRAINT_SET_HPP_