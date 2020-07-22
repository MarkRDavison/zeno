#include <zeno/Interaction/ConstraintSet.hpp>
#include <zeno/Interaction/Constraint.hpp>

namespace ze {

	ConstraintSet::ConstraintSet() {

	}
	ConstraintSet::ConstraintSet(
		std::shared_ptr<Constraint> _xConstraint,
		std::shared_ptr<Constraint> _yConstraint,
		std::shared_ptr<Constraint> _widthConstraint,
		std::shared_ptr<Constraint> _heightConstraint)
	:
		xConstraint(_xConstraint),
		yConstraint(_yConstraint),
		widthConstraint(_widthConstraint),
		heightConstraint(_heightConstraint) {
	}
	void ConstraintSet::notify(std::shared_ptr<Component> _current, std::shared_ptr<Component> _parent) {
		if (xConstraint) { xConstraint->notify(_current, _parent, *this); }
		if (yConstraint) { yConstraint->notify(_current, _parent, *this); }
		if (widthConstraint) { widthConstraint->notify(_current, _parent, *this); }
		if (heightConstraint) { heightConstraint->notify(_current, _parent, *this); }
	}

}