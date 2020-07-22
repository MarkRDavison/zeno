#ifndef INCLUDED_ZENO_INTERACTION_CONSTRAINTS_FILL_CONSTRAINT_HPP_
#define INCLUDED_ZENO_INTERACTION_CONSTRAINTS_FILL_CONSTRAINT_HPP_

#include <zeno/Interaction/Constraint.hpp>

namespace ze {

	class FillConstraint : public Constraint {
	public:
		FillConstraint();
		FillConstraint(float _margin);
		~FillConstraint() override = default;

		float getRelativeValue() override;
		void setPixelValue(int _pixels) override;
		void setRelativeValue(float _value) override;
	private:
		float m_Margin;

	};

}

#endif // INCLUDED_ZENO_INTERACTION_CONSTRAINTS_FILL_CONSTRAINT_HPP_