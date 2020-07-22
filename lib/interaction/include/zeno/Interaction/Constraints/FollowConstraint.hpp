#ifndef INCLUDED_ZENO_INTERACTION_CONSTRAINTS_FOLLOWER_CONSTRAINT_HPP_
#define INCLUDED_ZENO_INTERACTION_CONSTRAINTS_FOLLOWER_CONSTRAINT_HPP_

#include <zeno/Interaction/Constraint.hpp>
#include <zeno/Interaction/ConstraintTypes.hpp>
#include <memory>

namespace ze {

	class FollowConstraint : public Constraint {
	public:
		FollowConstraint(Component* _other, ConstraintType _type);
		FollowConstraint(Component* _other, float _margin);
		~FollowConstraint() override = default;

		float getRelativeValue() override;
		void setPixelValue(int _pixels) override;
		void setRelativeValue(float _value) override;
		void finishSetup(ConstraintSet& _set) override;

	private:
		Component *m_Other;
		float m_Margin;
		ConstraintType m_Type{ ConstraintType::NONE };
		std::shared_ptr<Constraint> m_MarginConstraint;
	};

}

#endif // INCLUDED_ZENO_INTERACTION_CONSTRAINTS_FOLLOWER_CONSTRAINT_HPP_