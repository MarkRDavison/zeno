#include <zeno/Interaction/Constraints/FillConstraint.hpp>
#include <zeno/Interaction/Component.hpp>

namespace ze {
	FillConstraint::FillConstraint() : FillConstraint(0.0f) {}
	FillConstraint::FillConstraint(float _margin) :
		m_Margin(_margin) {

	}

	float FillConstraint::getRelativeValue() {
		const float pos = m_PositionConstraint->getRelativeValue();
		const float gap = m_Margin / ( 
			xAxis
				? parent->getPixelWidth()
				: parent->getPixelHeight());
		return 1.0f - gap - pos;
	}
	void FillConstraint::setPixelValue(int _pixels) {
		m_Margin = static_cast<float>(_pixels);
		notifyDimensionChange();
	}
	void FillConstraint::setRelativeValue(float _value) {
		const float parentSize = xAxis
			? parent->getPixelWidth()
			: parent->getPixelHeight();

		setPixelValue(static_cast<int>(_value / parentSize));
	}
	void FillConstraint::finishSetup(ConstraintSet& _set) {
		m_PositionConstraint = xAxis
			? _set.xConstraint
			: _set.yConstraint;
	}

}