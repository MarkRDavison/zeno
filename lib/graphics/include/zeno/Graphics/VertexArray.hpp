#ifndef INCLUDED_ZENO_GRAPHICS_VERTEX_ARRAY_HPP_
#define INCLUDED_ZENO_GRAPHICS_VERTEX_ARRAY_HPP_

#include <zeno/Core/Rect.hpp>
#include <zeno/Graphics/Renderable.hpp>
#include <zeno/Graphics/Vertex.hpp>
#include <vector>

namespace ze {

    class VertexArray : public Renderable {
    public:
        VertexArray();
        VertexArray(std::size_t _size);
        ~VertexArray();

        void clear();
        void create();
        std::size_t size() const;

        Vertex& operator[](std::size_t _index);
        const Vertex& operator[](std::size_t _index) const;

        void appendVertex(const Vertex& _vertex);

        unsigned getVao() const noexcept { return m_Vao; }

        void render(const Window& _window, RenderInfo _info) const override;

        ze::FloatRect getBounds() const;
        void calculateBounds();

    private:
        bool m_Created{ false };
        std::vector<Vertex> m_Verticies;
        unsigned m_Vao{ 0 };
        unsigned m_Vbo{ 0 };

        FloatRect m_Bounds;
    };

}

#endif // INCLUDED_ZENO_GRAPHICS_VERTEX_ARRAY_HPP_