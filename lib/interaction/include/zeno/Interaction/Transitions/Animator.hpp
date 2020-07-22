#ifndef INCLUDED_ZENO_INTERACTION_TRANSITIONS_ANIMATOR_HPP_
#define INCLUDED_ZENO_INTERACTION_TRANSITIONS_ANIMATOR_HPP_

#include <zeno/Interaction/InteractionForward.hpp>
#include <zeno/Interaction/Transitions/Transition.hpp>
#include <unordered_map>
#include <memory>

namespace ze {

	using TransitionModifiers = std::unordered_map<TransitionId, std::shared_ptr<Modifier>>;

	class Animator {
	public:
		Animator(std::shared_ptr<Component> _component);

		void applyModdifiers(std::shared_ptr<Transition> _transition, bool _reverse, float _delay);
		bool isDoingTransition(TransitionId _transitionId) const;

		void update(float _delta);


		void resetValues();

		float getX() const;
		float getY() const;
		float getWidth() const;
		float getHeight() const;
		float getAlpha() const;

		void applyX(float _x, bool _change);
		void applyY(float _y, bool _change);
		void applyWidth(float _width, bool _change);
		void applyHeight(float _height, bool _change);
		void applyAlpha(float _alpha, bool _change);

	private:
		void updateComponentAsNecessary() const;

		std::shared_ptr<Component> m_Component;
		TransitionModifiers m_Modifiers;

		float m_X{ 0.0f };
		float m_Y{ 0.0f };
		float m_Width{ 1.0f };
		float m_Height{ 1.0f };
		float m_Alpha{ 1.0f };
		bool m_PositionChange{ false };
		bool m_ScaleChange{ false };
		bool m_AlphaChange{ false };
	};

}

#endif // INCLUDED_ZENO_INTERACTION_TRANSITIONS_ANIMATOR_HPP_