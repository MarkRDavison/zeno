#include <zeno/Graphics/VertexArray.hpp>
#include <GL/glew.h>
#include <cassert>
#include <iostream>

namespace ze {

    VertexArray::VertexArray() : VertexArray(0) {

    }

    VertexArray::VertexArray(std::size_t _size) :
        m_Verticies(_size) {
    }

    VertexArray:: ~VertexArray() {
        glDeleteBuffers(1, &m_Vbo);
        glDeleteVertexArrays(1, &m_Vao);
    }

    void VertexArray::clear() {
        m_Verticies.clear();
        m_Created = false;
        glDeleteBuffers(1, &m_Vbo);
        glDeleteVertexArrays(1, &m_Vao);
    }
    void VertexArray::create() {
        glDeleteBuffers(1, &m_Vbo);
        glDeleteVertexArrays(1, &m_Vao);
        if (m_Verticies.empty()) {
            m_Created = false;
            return;
        }

        float* data = reinterpret_cast<float*>(m_Verticies.data());

        glGenVertexArrays(1, &m_Vao);
        glBindVertexArray(m_Vao);

        glGenBuffers(1, &m_Vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * size(), data, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(7 * sizeof(float)));

        m_Created = true;
        calculateBounds();
    }
    std::size_t VertexArray::size() const {
        return m_Verticies.size();
    }

    Vertex& VertexArray::operator[](std::size_t _index) {
        assert(_index < m_Verticies.size());
        return m_Verticies[_index];
    }
    const Vertex& VertexArray::operator[](std::size_t _index) const {
        assert(_index < m_Verticies.size());
        return m_Verticies[_index];
    }

    void VertexArray::appendVertex(const Vertex& _vertex) {
        m_Verticies.emplace_back(_vertex);
    }

    void VertexArray::render(const Window& _window, RenderInfo _info) const {
        if (!m_Created) {
            std::cerr << "Trying to draw vertex array that hasn't been created" << std::endl;
        }

        if (_info.shader == nullptr) {
            if (_info.texture == nullptr) {
                _info.shader = &Shader::VertexArrayShader;
            } else {
                _info.shader = &Shader::VertexArrayTextureShader;
            }
        }
        assert(_info.shader != nullptr);

        _info.shader->bind();

        if (_info.texture != nullptr) {
            _info.texture->bind();
        }

        _info.shader->passUniform("model", _info.model);
        _info.shader->passUniform("view", _info.view);
        _info.shader->passUniform("projection", _info.projection);

        glBindVertexArray(getVao());
        glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(size()));
        glBindVertexArray(0);

        if (_info.texture != nullptr) {
            ze::Texture::unbind();
        }
        if (_info.shader != nullptr) {
            ze::Shader::unbind();
        }
    }
    ze::FloatRect VertexArray::getBounds() const {
        return m_Bounds;
    }
    void VertexArray::calculateBounds() {

        float minX = std::numeric_limits<float>().max();
        float maxX = std::numeric_limits<float>().min();
        float minY = std::numeric_limits<float>().max();
        float maxY = std::numeric_limits<float>().min();

        for (const auto& vertex : m_Verticies) {
            minX = std::min(minX, vertex.position.x);
            maxX = std::max(maxX, vertex.position.x);
            minY = std::min(minY, vertex.position.y);
            maxY = std::max(maxY, vertex.position.y);
        }

        m_Bounds = FloatRect(minX, minY, maxX - minX, maxY - minY);
    }

}
