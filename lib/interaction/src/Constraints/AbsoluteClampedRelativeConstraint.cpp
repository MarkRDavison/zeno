#include <zeno/Interaction/Constraints/AbsoluteClampedRelativeConstraint.hpp>

namespace ze {

	AbsoluteClampedRelativeConstraint::AbsoluteClampedRelativeConstraint(float _relativeValue, float _min, float _max) :
		m_RelativeValue(_relativeValue),
		m_Min(_min),
		m_Max(_max) {

	}

	float AbsoluteClampedRelativeConstraint::getRelativeValue() {
		const auto parentPixelSize = getParentPixelSize();
		const auto relativePixels = m_RelativeValue * parentPixelSize;

		if (relativePixels < m_Min) {
			return m_Min / parentPixelSize;
		}

		if (relativePixels > m_Max) {
			return m_Max / parentPixelSize;
		}

		return m_RelativeValue;
	}
	void AbsoluteClampedRelativeConstraint::setPixelValue(int _pixels) {
		setRelativeValue(_pixels / getParentPixelSize());
	}
	void AbsoluteClampedRelativeConstraint::setRelativeValue(float _value) {
		if (m_RelativeValue != _value) {
			m_RelativeValue = _value;
			notifyDimensionChange();
		}
	}
	void AbsoluteClampedRelativeConstraint::setMinValue(int _minPixels) {
		m_Min = static_cast<float>(_minPixels);
	}
	void AbsoluteClampedRelativeConstraint::setMaxValue(int _maxPixels) {
		m_Max = static_cast<float>(_maxPixels);
	}

}