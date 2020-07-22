#ifndef INCLUDED_ZENO_INTERACTION_COMPONENT_HPP_
#define INCLUDED_ZENO_INTERACTION_COMPONENT_HPP_

#include <zeno/Interaction/InteractionForward.hpp>
#include <zeno/Interaction/ConstraintSet.hpp>
#include <zeno/Core/Vector2.hpp>
#include <zeno/Core/Rect.hpp>
#include <zeno/Graphics.hpp>
#include <vector>
#include <memory>

namespace ze {

	class Component {
	public:
		virtual ~Component() = 0;

		virtual bool handleEvent(const ze::Event& _event) = 0;

		void forceInitialisation(const ze::FloatRect& _bounds);
		void forceInitialisation(float _x, float _y, float _width, float _height);

		void notifyDimensionChange();
		void updateTotalAlpha();

		void recalculatePositions();

		void initialise();
		void initialiseAllChildren();
		void initialiseChild(std::shared_ptr<Component> _child);
		void reset();

		float getPixelWidth() const;
		float getPixelHeight() const;
		float getAbsAspectRatio() const;
		float getRelativeHeightCoords(float relativeWidth) const;
		float getRelativeWidthCoords(float relativeHeight) const;

		void addComponent(std::shared_ptr<Component> _component);
		void addComponent(std::shared_ptr<Component> _component, ConstraintSet _constraintSet);

		virtual void update(float _delta);
		void render(const ze::Window& _window, ze::RenderInfo _info) const;
		virtual void renderComponent(const ze::Window& _window, ze::RenderInfo _info) const = 0;

		int level{ 0 };

		float x{ 0.0f };
		float y{ 0.0f };
		float width{ 1.0f };
		float height{ 1.0f };

		bool initialised{ false };
		bool reloadOnSizeChange{ false };

		ConstraintSet constraintSet;

		const Desktop* desktop{ nullptr };
		std::shared_ptr<Component> parent;
		std::shared_ptr<Animator> animator;
		std::vector<std::shared_ptr<Component>> children;

	private:
		static float getConstraintRelativeOr(std::shared_ptr<Constraint> _constraint, float _fallback);
	};

	inline Component::~Component() = default;
}

#endif // INCLUDED_ZENO_INTERACTION_COMPONENT_HPP_