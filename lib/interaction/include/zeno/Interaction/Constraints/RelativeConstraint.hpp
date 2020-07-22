#ifndef INCLUDED_ZENO_INTERACTION_CONSTRAINTS_RELATIVE_CONSTRAINT_HPP_
#define INCLUDED_ZENO_INTERACTION_CONSTRAINTS_RELATIVE_CONSTRAINT_HPP_

#include <zeno/Interaction/Constraint.hpp>

namespace ze {

	class RelativeConstraint : public Constraint {
	public:
		RelativeConstraint(float _relativeValue);
		~RelativeConstraint() override = default;

		float getRelativeValue() override;
		void setPixelValue(int _pixels) override;
		void setRelativeValue(float _value) override;

	private:
		float m_RelativeValue;
	};

}

#endif // INCLUDED_ZENO_INTERACTION_CONSTRAINTS_RELATIVE_CONSTRAINT_HPP_