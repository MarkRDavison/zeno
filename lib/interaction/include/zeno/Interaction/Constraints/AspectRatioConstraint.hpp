#ifndef INCLUDED_ZENO_INTERACTION_CONSTRAINTS_ASPECT_RATIO_CONSTRAINT_HPP_
#define INCLUDED_ZENO_INTERACTION_CONSTRAINTS_ASPECT_RATIO_CONSTRAINT_HPP_

#include <zeno/Interaction/Constraint.hpp>

namespace ze {

	class AspectRatioConstraint : public Constraint {
	public:
		AspectRatioConstraint(float _aspectRatio);
		~AspectRatioConstraint() override = default;

		float getRelativeValue() override;
		void setPixelValue(int _pixels) override;
		void setRelativeValue(float _value) override;
		void finishSetup(ConstraintSet& _set) override;

	private:
		float m_AspectRatio;
		std::shared_ptr<Constraint> otherConstraint;
	};

}
#endif // INCLUDED_ZENO_INTERACTION_CONSTRAINTS_ASPECT_RATIO_CONSTRAINT_HPP_