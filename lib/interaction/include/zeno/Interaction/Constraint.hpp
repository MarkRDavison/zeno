#ifndef INCLUDED_ZENO_INTERACTION_CONSTRAINT_HPP_
#define INCLUDED_ZENO_INTERACTION_CONSTRAINT_HPP_

#include <zeno/Interaction/InteractionForward.hpp>
#include <memory>

namespace ze {

	class Constraint {
	public:
		virtual ~Constraint() = 0;

		void setAxis(bool _xAxis);
		void setAxis(bool _xAxis, bool _positionConstraint);
		void notify(std::shared_ptr<Component> _current, std::shared_ptr<Component> _parent, ConstraintSet& _set);

		void notifyDimensionChange();

		float getParentPixelSize();

		virtual float getRelativeValue() = 0;
		virtual void setPixelValue(int _pixels) = 0;
		virtual void setRelativeValue(float _value) = 0;
		virtual void finishSetup(ConstraintSet& _set) {}

		bool xAxis{ false };
		bool positionConstraint{ false };

		std::shared_ptr<Component> current;
		std::shared_ptr<Component> parent;
	};

	inline Constraint::~Constraint() = default;

}

#endif // INCLUDED_ZENO_INTERACTION_CONSTRAINT_HPP_