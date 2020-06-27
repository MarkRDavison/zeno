#ifndef INCLUDED_ZENO_GRAPHICS_SHAPE_HPP
#define INCLUDED_ZENO_GRAPHICS_SHAPE_HPP

#include <zeno/Graphics/Colour.hpp>
#include <zeno/Graphics/Renderable.hpp>
#include <zeno/Core/Mat4x4.hpp>
#include <zeno/Core/Rect.hpp>
#include <zeno/Core/Transformable2D.hpp>
#include <zeno/Core/Vector2.hpp>
#include <vector>

namespace ze {

	class Shape : public Transformable2D, public Renderable {
	public:
		Shape(void);

		virtual ~Shape(void);

		void setInternalColour(const Colour& _colour);
		void setOutlineColour(const Colour& _colour);

		void setOutlineThickness(float _thickness);

		FloatRect getBounds(void) const;

		void render(const Window& _window, RenderInfo _info) const override;

	protected:
		void updateInternalPositions(void);
		void updateOutlinePositions(void);

		void updateInternalColours(void);
		void updateOutlineColours(void);

	protected:
		std::vector<Vector2f> m_Points;

		Colour m_InternalColour;
		Colour m_OutlineColour;

		float m_OutlineThickness;

		FloatRect m_InternalBounds;
		FloatRect m_OutlineBounds;

		unsigned int m_PointsToRender;
		unsigned int m_OutlinePointsToRender;

		unsigned int m_InternalVAO;
		unsigned int m_InternalPositionVBO;
		unsigned int m_InternalColourVBO;

		unsigned int m_OutlineVAO;
		unsigned int m_OutlinePositionVBO;
		unsigned int m_OutlineColourVBO;
	};

}

#endif //~ INCLUDED_ZENO_GRAPHICS_SHAPE_HPP