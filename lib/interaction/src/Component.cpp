#include <zeno/Interaction/Component.hpp>
#include <zeno/Interaction/Constraint.hpp>
#include <zeno/Interaction/Desktop.hpp>
#include <zeno/Interaction/Transitions/Animator.hpp>

#define X_MODIFIER 0.0f
#define Y_MODIFIER 0.0f
#define WIDTH_MODIFIER 1.0f
#define HEIGHT_MODIFIER 1.0f
#define GET_ANIM_X 0.0f
#define GET_ANIM_Y 0.0f
#define GET_ANIM_WIDTH 1.0f
#define GET_ANIM_HEIGHT 1.0f

namespace ze {

	void Component::forceInitialisation(const ze::FloatRect& _bounds) {
		forceInitialisation(_bounds.left, _bounds.bot, _bounds.width, _bounds.height);
	}
	void Component::forceInitialisation(float _x, float _y, float _width, float _height) {
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		initialised = true;
	}
	void Component::notifyDimensionChange() {
		recalculatePositions();

		for (auto& c : children) {
			c->notifyDimensionChange();
		}
	}
	void Component::updateTotalAlpha() {
		throw std::runtime_error("Component::updateTotalAlpha not implemented");
	}

	void Component::recalculatePositions() {
		x = parent->x + (getConstraintRelativeOr(constraintSet.xConstraint, 0.0f) + X_MODIFIER + GET_ANIM_X) * parent->width;
		y = parent->y + (getConstraintRelativeOr(constraintSet.yConstraint, 0.0f) + Y_MODIFIER + GET_ANIM_Y) * parent->height;

		width = getConstraintRelativeOr(constraintSet.widthConstraint, 1.0f) * parent->width * WIDTH_MODIFIER * GET_ANIM_WIDTH;
		height = getConstraintRelativeOr(constraintSet.heightConstraint, 1.0f) * parent->height * HEIGHT_MODIFIER * GET_ANIM_HEIGHT;
	}

	void Component::initialiseAllChildren() {

	}
	void Component::initialiseChild(std::shared_ptr<Component> _child) {
		children.push_back(_child);
		_child->desktop = desktop;
		_child->level = std::max(level, _child->level);
		_child->recalculatePositions();
		_child->initialise();
		_child->initialiseAllChildren();
	}
	void Component::reset() {

	}

	float Component::getPixelWidth() const {
		return width * desktop->getPixelSize().x;
	}
	float Component::getPixelHeight() const {
		return height * desktop->getPixelSize().y;
	}
	float Component::getAbsAspectRatio() const {
		return getPixelWidth() / getPixelHeight();
	}
	float Component::getRelativeHeightCoords(float relativeWidth) const {
		return relativeWidth * getAbsAspectRatio();
	}

	float Component::getRelativeWidthCoords(float relativeHeight) const {
		return relativeHeight / getAbsAspectRatio();
	}
	void Component::addComponent(std::shared_ptr<Component> _component) {
		addComponent(_component, {});
	}
	void Component::addComponent(std::shared_ptr<Component> _component, ConstraintSet _constraintSet) {
		_component->constraintSet.xConstraint = _constraintSet.xConstraint;
		_component->constraintSet.yConstraint = _constraintSet.yConstraint;
		_component->constraintSet.widthConstraint = _constraintSet.widthConstraint;
		_component->constraintSet.heightConstraint = _constraintSet.heightConstraint;

		if (_component->constraintSet.xConstraint) {
			_component->constraintSet.xConstraint->setAxis(true, true);
		}
		if (_component->constraintSet.widthConstraint) {
			_component->constraintSet.widthConstraint->setAxis(true, false);
		}
		if (_component->constraintSet.yConstraint) {
			_component->constraintSet.yConstraint->setAxis(false, true);
		}
		if (_component->constraintSet.heightConstraint) {
			_component->constraintSet.heightConstraint->setAxis(false, false);
		}

		auto tt = std::shared_ptr<Component>(this);
		_component->constraintSet.notify(_component, tt);
		_component->parent = tt;
		_component->desktop = desktop;
		initialiseChild(_component);
		// TODO: Lists of things to add/remove
	}

	void Component::update(float _delta) {
		if (animator) {
			animator->update(_delta);
		}
		for (auto& c : children) {
			c->update(_delta);
		}
	}
	void Component::render(const ze::RenderTarget& _target, ze::RenderInfo _info) const {
		renderComponent(_target, _info);

		for (const auto& c : children) {
			c->render(_target, _info);
		}
	}

	float Component::getConstraintRelativeOr(std::shared_ptr<Constraint> _constraint, float _fallback) {
		if (_constraint) {
			return _constraint->getRelativeValue();
		}
		return _fallback;
	}
}