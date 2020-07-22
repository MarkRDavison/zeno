#include <zeno/Interaction/Controls/ButtonControl.hpp>

namespace ze {

	void ButtonControl::update(float _delta) {
		ClickableControl::update(_delta);
	}
	bool ButtonControl::onClick(ze::Mouse::Button _button) {
		clickSignal(_button);
		return true;
	}

	void ButtonControl::renderComponent(const ze::Window& _window, ze::RenderInfo _info) const {
		ze::VertexArray v(ze::DrawType::Triangles);

		ze::Colour colour = m_MouseOver
			? hoverColour
			: defaultColour;

		v.appendVertex(ze::Vertex(ze::Vector3f(x, y, (float)level), colour));
		v.appendVertex(ze::Vertex(ze::Vector3f(x + width, y, (float)level), colour));
		v.appendVertex(ze::Vertex(ze::Vector3f(x + width, y + height, (float)level), colour));
		v.appendVertex(ze::Vertex(ze::Vector3f(x, y, (float)level), colour));
		v.appendVertex(ze::Vertex(ze::Vector3f(x + width, y + height, (float)level), colour));
		v.appendVertex(ze::Vertex(ze::Vector3f(x, y + height, (float)level), colour));

		v.create();

		v.render(_window, _info);
	}

}