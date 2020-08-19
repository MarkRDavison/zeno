#include <zeno/Interaction/Controls/BlockControl.hpp>
#include <zeno/Graphics/Texture.hpp>

namespace ze {


	bool BlockControl::handleEvent(const ze::Event& _event) { 
		for (auto& c : children) {
			if (c->handleEvent(_event)) {
				return true;
			}
		}
		return false;
	}
	
	void BlockControl::renderComponent(const ze::RenderTarget& _target, ze::RenderInfo _info) const {
		ze::RenderInfo info(_info);
		info.texture = texture;
		ze::VertexArray v(ze::DrawType::Triangles);

		ze::Vector2f texSize(1.0f, 1.0f);
		if (info.texture != nullptr) {
			texSize = ze::Vector2f(info.texture->getSize());
		}

		v.appendVertex(ze::Vertex(ze::Vector3f(x, y, (float)level), colour, ze::Vector2f((textureBounds.left) / texSize.x, (textureBounds.bot) / texSize.y)));
		v.appendVertex(ze::Vertex(ze::Vector3f(x + width, y, (float)level), colour, ze::Vector2f((textureBounds.left + textureBounds.width) / texSize.x, (textureBounds.bot) / texSize.y)));
		v.appendVertex(ze::Vertex(ze::Vector3f(x + width, y + height, (float)level), colour, ze::Vector2f((textureBounds.left + textureBounds.width) / texSize.x, (textureBounds.bot + textureBounds.height) / texSize.y)));
		v.appendVertex(ze::Vertex(ze::Vector3f(x, y, (float)level), colour, ze::Vector2f((textureBounds.left) / texSize.x, (textureBounds.bot) / texSize.y)));
		v.appendVertex(ze::Vertex(ze::Vector3f(x + width, y + height, (float)level), colour, ze::Vector2f((textureBounds.left + textureBounds.width) / texSize.x, (textureBounds.bot + textureBounds.height) / texSize.y)));
		v.appendVertex(ze::Vertex(ze::Vector3f(x, y + height, (float)level), colour, ze::Vector2f((textureBounds.left) / texSize.x, (textureBounds.bot + textureBounds.height) / texSize.y)));

		v.create();

		v.render(_target, info);
	}

}