#ifndef INCLUDED_ZENO_INTERACTION_CONSTRAINTS_BEST_FIT_CONSTRAINT_HPP_
#define INCLUDED_ZENO_INTERACTION_CONSTRAINTS_BEST_FIT_CONSTRAINT_HPP_

#include <zeno/Interaction/Constraint.hpp>

namespace ze {

	class BestFitConstraint : public Constraint {
	public:
		BestFitConstraint(float _aspectRatio);
		~BestFitConstraint() override = default;

		float getRelativeValue() override;
		void setPixelValue(int _pixels) override;
		void setRelativeValue(float _value) override;

	private:
		float m_AspectRatio;
	};

}

#endif // INCLUDED_ZENO_INTERACTION_CONSTRAINTS_BEST_FIT_CONSTRAINT_HPP_