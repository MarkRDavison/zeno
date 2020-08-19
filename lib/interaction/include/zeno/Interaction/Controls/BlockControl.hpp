#ifndef INCLUDED_ZENO_INTERACTION_CONTROLS_BLOCK_CONTROL_HPP_
#define INCLUDED_ZENO_INTERACTION_CONTROLS_BLOCK_CONTROL_HPP_

#include <zeno/Interaction/Component.hpp>

namespace ze {

	class Texture;
	class BlockControl : public Component {
	public:
		~BlockControl() override = default;
		bool handleEvent(const ze::Event & _event) override;
		void renderComponent(const ze::RenderTarget& _target, ze::RenderInfo _info) const override;

		ze::Colour colour{ ze::Colour::Magenta };
		ze::Texture* texture{ nullptr };
		ze::FloatRect textureBounds;
	};

}

#endif // INCLUDED_ZENO_INTERACTION_CONTROLS_BLOCK_CONTROL_HPP_