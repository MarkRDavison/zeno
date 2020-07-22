#include <zeno/Interaction/Constraints/FollowConstraint.hpp>
#include <zeno/Interaction/Component.hpp>

namespace ze {

	FollowConstraint::FollowConstraint(Component* _other, ConstraintType _type) :
		m_Other(_other),
		m_Margin(0.0f), 
		m_Type(_type)
	{

	}
	FollowConstraint::FollowConstraint(Component* _other, float _margin) :
		m_Other(_other),
		m_Margin(_margin) {

	}

	float FollowConstraint::getRelativeValue() {

		float relative;
		if (m_MarginConstraint) {
			relative = m_MarginConstraint->getRelativeValue();
			if (xAxis != m_MarginConstraint->xAxis) {
				const auto otherParent = m_MarginConstraint->getParentPixelSize();
				const auto thisParent = getParentPixelSize();
				relative /= thisParent;
				relative *= otherParent;
			}

		} else {
			relative = m_Margin / (xAxis
				? parent->getPixelWidth()
				: parent->getPixelHeight());
		}

		const float siblingPosition = xAxis
			? m_Other->constraintSet.xConstraint->getRelativeValue()
			: m_Other->constraintSet.yConstraint->getRelativeValue();

		const float siblingSize = xAxis
			? m_Other->constraintSet.widthConstraint->getRelativeValue()
			: m_Other->constraintSet.heightConstraint->getRelativeValue();

		return relative + siblingPosition + siblingSize;
	}
	void FollowConstraint::setPixelValue(int _pixels) {
		m_Margin = static_cast<float>(_pixels);
		notifyDimensionChange();
	}
	void FollowConstraint::setRelativeValue(float _value) {
		setPixelValue(static_cast<int>(_value *
			(xAxis
				? parent->getPixelWidth()
				: parent->getPixelHeight())
		));
	}

	void FollowConstraint::finishSetup(ConstraintSet& _set) {
		switch (m_Type) {
		case ConstraintType::X_POS:
			m_MarginConstraint = _set.xConstraint;
			break;
		case ConstraintType::Y_POS:
			m_MarginConstraint = _set.yConstraint;
			break;
		}
	}
}