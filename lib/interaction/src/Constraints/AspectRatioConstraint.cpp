#include <zeno/Interaction/Constraints/AspectRatioConstraint.hpp>
#include <zeno/Interaction/ConstraintSet.hpp>
#include <zeno/Interaction/Component.hpp>
#include <zeno/Interaction/Desktop.hpp>

namespace ze {

	AspectRatioConstraint::AspectRatioConstraint(float _aspectRatio) :
		m_AspectRatio(_aspectRatio) {

	}

	float AspectRatioConstraint::getRelativeValue() {
		float otherRelValue = otherConstraint->getRelativeValue();
		float relValue = xAxis 
			? parent->getRelativeWidthCoords(otherRelValue)
			: parent->getRelativeHeightCoords(otherRelValue);
		return relValue * m_AspectRatio;
	}
	void AspectRatioConstraint::setPixelValue(int _pixels) { }
	void AspectRatioConstraint::setRelativeValue(float _value) { }

	void AspectRatioConstraint::finishSetup(ConstraintSet& _set) {
		if (positionConstraint) {
			otherConstraint = xAxis ? _set.yConstraint : _set.xConstraint;
		} else {
			otherConstraint = xAxis ? _set.heightConstraint : _set.widthConstraint;
		}
	}
}