#ifndef INCLUDED_ZENO_GRAPHICS_VERTEX_ARRAY_HPP_
#define INCLUDED_ZENO_GRAPHICS_VERTEX_ARRAY_HPP_

#include <zeno/Core/Rect.hpp>
#include <zeno/Graphics/Renderable.hpp>
#include <zeno/Graphics/Vertex.hpp>
#include <vector>

namespace ze {

    enum class DrawType {
        Triangles,
        Lines,
        LineStrip
    };

    class VertexArray : public Renderable {
    public:
        VertexArray();
        VertexArray(DrawType _type);
        VertexArray(std::size_t _size);
        VertexArray(DrawType _type, std::size_t _size);
        ~VertexArray();

        void clear();
        void create();
        std::size_t size() const;

        Vertex& operator[](std::size_t _index);
        const Vertex& operator[](std::size_t _index) const;

        void appendVertex(const Vertex& _vertex);

        unsigned getVao() const noexcept { return m_Vao; }

        void render(const RenderTarget& _target, RenderInfo _info) const override;

        void setDrawType(DrawType _type);
        DrawType getDrawType() const;

        ze::FloatRect getBounds() const;
        void calculateBounds();
    private:
        bool m_Created{ false };
        DrawType m_Type{ DrawType::Triangles };
        std::vector<Vertex> m_Verticies;
        unsigned m_Vao{ 0 };
        unsigned m_Vbo{ 0 };

        FloatRect m_Bounds;

    };

}

#endif // INCLUDED_ZENO_GRAPHICS_VERTEX_ARRAY_HPP_