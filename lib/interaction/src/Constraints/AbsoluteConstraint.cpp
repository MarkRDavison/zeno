#include <zeno/Interaction/Constraints/AbsoluteConstraint.hpp>

namespace ze {

	AbsoluteConstraint::AbsoluteConstraint() : AbsoluteConstraint(0.0f) {}
	AbsoluteConstraint::AbsoluteConstraint(float _absoluteValue) :
		m_AbsoluteValue(_absoluteValue) {

	}

	float AbsoluteConstraint::getRelativeValue() {
		const auto parentSize = getParentPixelSize();
		const auto relative = m_AbsoluteValue / parentSize;
		return relative;
	}
	void AbsoluteConstraint::setPixelValue(int _pixels) {
		if (m_AbsoluteValue != (float)_pixels) {
			m_AbsoluteValue = (float)_pixels;
			notifyDimensionChange();
		}
	}
	void AbsoluteConstraint::setRelativeValue(float _value) {
		setPixelValue(static_cast<int>(getParentPixelSize() * _value));
	}

}