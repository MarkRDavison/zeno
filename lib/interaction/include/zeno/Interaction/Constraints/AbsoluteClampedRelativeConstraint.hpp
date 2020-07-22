#ifndef INCLUDED_ZENO_INTERACTION_CONSTRAINTS_ABSOLUTE_CLAMPED_RELATIVE_CONSTRAINT_HPP_
#define INCLUDED_ZENO_INTERACTION_CONSTRAINTS_ABSOLUTE_CLAMPED_RELATIVE_CONSTRAINT_HPP_

#include <zeno/Interaction/Constraint.hpp>

namespace ze {

	class AbsoluteClampedRelativeConstraint : public Constraint {
	public:
		AbsoluteClampedRelativeConstraint(float _relativeValue, float _min, float _max);
		~AbsoluteClampedRelativeConstraint() override = default;

		float getRelativeValue() override;
		void setPixelValue(int _pixels) override;
		void setRelativeValue(float _value) override;

		void setMinValue(int _minPixels);
		void setMaxValue(int _maxPixels);

	private:
		float m_RelativeValue;
		float m_Min;
		float m_Max;
	};

}

#endif // INCLUDED_ZENO_INTERACTION_CONSTRAINTS_ABSOLUTE_CLAMPED_RELATIVE_CONSTRAINT_HPP_