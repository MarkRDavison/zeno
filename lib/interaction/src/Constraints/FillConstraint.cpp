#include <zeno/Interaction/Constraints/FillConstraint.hpp>
#include <zeno/Interaction/Component.hpp>

namespace ze {
	FillConstraint::FillConstraint() : FillConstraint(0.0f) {}
	FillConstraint::FillConstraint(float _margin) :
		m_Margin(_margin) {

	}

	float FillConstraint::getRelativeValue() {
		float gap = m_Margin / ( 
			xAxis
				? parent->getPixelWidth()
				: parent->getPixelHeight());
		return 1.0f - gap * 2.0f;
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

}