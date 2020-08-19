#ifndef INCLUDED_ZENO_INTERACTION_CONSTRAINTS_DOCK_CONSTRAINT_HPP_
#define INCLUDED_ZENO_INTERACTION_CONSTRAINTS_DOCK_CONSTRAINT_HPP_

#include <zeno/Interaction/Constraint.hpp>
#include <memory>

namespace ze {

	enum class DockDirection {
		None,
		Left,
		Right,
		Top,
		Bottom
	};

	class DockConstraint : public Constraint {
	public:
		DockConstraint(DockDirection _dockDirection);
		~DockConstraint() override = default;

		float getRelativeValue() override;
		void setPixelValue(int _pixels) override;
		void setRelativeValue(float _value) override;
		void finishSetup(ConstraintSet& _set) override;

	private:
		DockDirection m_DockDirection;
		std::shared_ptr<Constraint> m_SizeConstraint;
	};

}

#endif // INCLUDED_ZENO_INTERACTION_CONSTRAINTS_DOCK_CONSTRAINT_HPP_