#ifndef INCLUDED_ZENO_INTERACTION_CONSTRAINTS_ABSOLUTE_CONSTRAINT_HPP_
#define INCLUDED_ZENO_INTERACTION_CONSTRAINTS_ABSOLUTE_CONSTRAINT_HPP_

#include <zeno/Interaction/Constraint.hpp>

namespace ze {

	class AbsoluteConstraint : public Constraint {
	public:
		AbsoluteConstraint();
		AbsoluteConstraint(float _absoluteValue);
		~AbsoluteConstraint() override = default;

		float getRelativeValue() override;
		void setPixelValue(int _pixels) override;
		void setRelativeValue(float _value) override;

	private:
		float m_AbsoluteValue;
	};

}

#endif // INCLUDED_ZENO_INTERACTION_CONSTRAINTS_ABSOLUTE_CONSTRAINT_HPP_