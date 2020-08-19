#include <zeno/Interaction/Constraints/DockConstraint.hpp>
#include <zeno/Interaction/ConstraintSet.hpp>

namespace ze {


	DockConstraint::DockConstraint(DockDirection _dockDirection) :
		m_DockDirection(_dockDirection) {

	}

	float DockConstraint::getRelativeValue() {
		if (m_DockDirection == DockDirection::Top ||
			m_DockDirection == DockDirection::Right) {
			return 1.0f - m_SizeConstraint->getRelativeValue();
		}
		return 0.0f;
	}
	void DockConstraint::setPixelValue(int _pixels) {
		throw "Invalid Operation";
	}
	void DockConstraint::setRelativeValue(float _value) {
		throw "Invalid Operation";
	}
	void DockConstraint::finishSetup(ConstraintSet& _set) {
		m_SizeConstraint = xAxis
			? _set.widthConstraint
			: _set.heightConstraint;
	}

}