#include <zeno/Interaction/Constraints/RelativeConstraint.hpp>

namespace ze {
	RelativeConstraint::RelativeConstraint(float _relativeValue) :
		m_RelativeValue(_relativeValue) {

	}

	float RelativeConstraint::getRelativeValue() {
		return m_RelativeValue;
	}
	void RelativeConstraint::setPixelValue(int _pixels) {
		setRelativeValue(_pixels / getParentPixelSize());
	}
	void RelativeConstraint::setRelativeValue(float _value) {
		if (m_RelativeValue != _value) {
			m_RelativeValue = _value;
			notifyDimensionChange();
		}
	}
}