#include <zeno/Interaction/Constraints/CenterConstraint.hpp>
#include <zeno/Interaction/ConstraintSet.hpp>

namespace ze {


	float CenterConstraint::getRelativeValue() {
		const auto size = sizeConstraint->getRelativeValue();
		return (1.0f - size) / 2.0f;
	}
	void CenterConstraint::setPixelValue(int _pixels) { }
	void CenterConstraint::setRelativeValue(float _value) { }
	void CenterConstraint::finishSetup(ConstraintSet& _set) {
		sizeConstraint = xAxis
			? _set.widthConstraint
			: _set.heightConstraint;
	}
}