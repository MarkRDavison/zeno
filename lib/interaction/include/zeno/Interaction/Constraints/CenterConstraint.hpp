#ifndef INCLUDED_ZENO_INTERACTION_CONSTRAINTS_CENTER_CONSTRAINT_HPP_
#define INCLUDED_ZENO_INTERACTION_CONSTRAINTS_CENTER_CONSTRAINT_HPP_

#include <zeno/Interaction/Constraint.hpp>

namespace ze {

	class CenterConstraint : public Constraint {
	public:
		~CenterConstraint() override = default;

		float getRelativeValue() override;
		void setPixelValue(int _pixels) override;
		void setRelativeValue(float _value) override;
		void finishSetup(ConstraintSet& _set) override;

		std::shared_ptr<Constraint> sizeConstraint;
	};

}

#endif // INCLUDED_ZENO_INTERACTION_CONSTRAINTS_CENTER_CONSTRAINT_HPP_