#ifndef INCLUDED_ZENO_GRAPHICS_VERTEX_HPP_
#define INCLUDED_ZENO_GRAPHICS_VERTEX_HPP_

#include <zeno/Core/Vector3.hpp>
#include <zeno/Graphics/Colour.hpp>

namespace ze {

	struct Vertex {

		Vertex() {}
		Vertex(const Vector2f& _position, const Colour& _colour) :
			Vertex({ _position, 0.0f }, _colour, {}) {

		}
		Vertex(const Vector3f& _position, const Colour& _colour) :
			Vertex(_position, _colour, {}) {

		}
		Vertex(const Vector2f& _position, const Colour& _colour, const Vector2f& _texture) :
			Vertex({ _position, 0.0f }, _colour, _texture) {

		}
		Vertex(const Vector3f& _position, const Colour& _colour, const Vector2f& _texture) :
			position(_position),
			colour(_colour),
			texture(_texture) {

		}

		Vector3f position;
		Colour colour;
		Vector2f texture;

	};

}

#endif // INCLUDED_ZENO_GRAPHICS_VERTEX_HPP_