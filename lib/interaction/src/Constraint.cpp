#include <zeno/Interaction/Constraint.hpp>
#include <zeno/Interaction/Component.hpp>

namespace ze {


	void Constraint::setAxis(bool _xAxis) {
		setAxis(_xAxis, positionConstraint);
	}
	void Constraint::setAxis(bool _xAxis, bool _positionConstraint) {
		xAxis = _xAxis;
		positionConstraint = _positionConstraint;
	}
	void Constraint::notify(std::shared_ptr<Component> _current, std::shared_ptr<Component> _parent, ConstraintSet& _set) {
		current = _current;
		parent = _parent;
		finishSetup(_set);
	}
	void Constraint::notifyDimensionChange() {
		current->notifyDimensionChange();
	}
	float Constraint::getParentPixelSize() {
		return xAxis 
			? parent->getPixelWidth() 
			: parent->getPixelHeight();
	}
}