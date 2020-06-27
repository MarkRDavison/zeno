#include <zeno/Graphics/Shader.hpp>
#include <GL/glew.h>
#include <iostream>
#include <zeno/Core/Vector2.hpp>
#include <zeno/Core/Vector3.hpp>
#include <zeno/Core/Vector4.hpp>
#include <zeno/Graphics/Colour.hpp>
#include <zeno/Core/Mat4x4.hpp>
#include <zeno/Utility/StringExtensions.hpp>

namespace ze {

    Shader Shader::VertexArrayShader;
    Shader Shader::VertexArrayTextureShader;

    void CheckStatus(GLuint obj) {
        GLint status = GL_FALSE;
        if (glIsShader(obj)) glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
        if (glIsProgram(obj)) glGetProgramiv(obj, GL_LINK_STATUS, &status);
        if (status == GL_TRUE) return;
        GLchar log[1 << 16] = { 0 };
        if (glIsShader(obj)) glGetShaderInfoLog(obj, sizeof(log), nullptr, log);
        if (glIsProgram(obj)) glGetProgramInfoLog(obj, sizeof(log), nullptr, log);
        std::cerr << log << std::endl;
        exit(-1);
    }

    Shader::~Shader() {
        glDeleteProgram(m_ProgramId);
    }

    bool Shader::loadShaderFiles(const std::string& _vertex, const std::string& _fragment) {
        m_Loaded = false;
        m_VertexSource = StringExtensions::loadFileToString(_vertex);
        m_FragmentSource = StringExtensions::loadFileToString(_fragment);

        return !(m_VertexSource.empty() || m_FragmentSource.empty());
    }
    bool Shader::createShader() {
        return createShader(m_VertexSource, m_FragmentSource);
    }
    bool Shader::createShader(const std::string& _vertex, const std::string& _fragment) {
        return createShader(_vertex, _fragment, {});
    }
    bool Shader::createShader(const std::string& _vertex, const std::string& _fragment, const std::vector<std::string>& _uniforms) {
        m_Loaded = false;
        if (m_ProgramId != 0) {
            glDeleteProgram(m_ProgramId);
        }
        m_ProgramId = glCreateProgram();

        {
            const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
            const char* source = _vertex.c_str();
            glShaderSource(vertexShader, 1, &source, nullptr);
            glCompileShader(vertexShader);

            glAttachShader(m_ProgramId, vertexShader);
            CheckStatus(vertexShader);
            glDeleteShader(vertexShader);
        }

        {
            const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            const char* source = _fragment.c_str();
            glShaderSource(fragmentShader, 1, &source, nullptr);
            glCompileShader(fragmentShader);

            glAttachShader(m_ProgramId, fragmentShader);
            CheckStatus(fragmentShader);
            glDeleteShader(fragmentShader);
        }

        glLinkProgram(m_ProgramId);
        CheckStatus(m_ProgramId);

        m_Loaded = true;

        for (const auto& u : _uniforms) {
            if (!findLocationOfUniform(u)) {
                return false;
            }
        }

        return true;
    }

    bool Shader::findLocationOfUniform(const std::string& _uniform) {
        if (m_UniformLocations.count(_uniform) > 0) {
            return false;
        }

        bind();

        const GLint loc = glGetUniformLocation(m_ProgramId, _uniform.c_str());

        if (loc == -1) {
            std::cerr << "glGetUniformLocation failed" << std::endl;
            return false;
        }

        m_UniformLocations[_uniform] = loc;
        unbind();

        return true;
    }

    void Shader::passUniform(const std::string& _name, float _uniform) {
        if (m_UniformLocations.count(_name) == 0) {
            std::cerr << "Get uniform: " << _name << " failed." << std::endl;
            return;
        }
        glUniform1f(m_UniformLocations[_name], _uniform);
    }
    void Shader::passUniform(const std::string& _name, const Vector2<float>& _uniform) {
        if (m_UniformLocations.count(_name) == 0) {
            std::cerr << "Get uniform: " << _name << " failed." << std::endl;
            return;
        }
        glUniform2f(m_UniformLocations[_name], _uniform.x, _uniform.y);
    }
    void Shader::passUniform(const std::string& _name, const Vector3<float>& _uniform) {
        if (m_UniformLocations.count(_name) == 0) {
            std::cerr << "Get uniform: " << _name << " failed." << std::endl;
            return;
        }
        glUniform3f(m_UniformLocations[_name], _uniform.x, _uniform.y, _uniform.z);
    }
    void Shader::passUniform(const std::string& _name, const Vector4<float>& _uniform) {
        if (m_UniformLocations.count(_name) == 0) {
            std::cerr << "Get uniform: " << _name << " failed." << std::endl;
            return;
        }
        glUniform4f(m_UniformLocations[_name], _uniform.x, _uniform.y, _uniform.z, _uniform.w);
    }
    void Shader::passUniform(const std::string& _name, const Colour& _uniform) {
        if (m_UniformLocations.count(_name) == 0) {
            std::cerr << "Get uniform: " << _name << " failed." << std::endl;
            return;
        }
        glUniform4f(m_UniformLocations[_name], _uniform.r, _uniform.g, _uniform.b, _uniform.a);
    }
    void Shader::passUniform(const std::string& _name, const Mat4x4& _uniform) {
        if (m_UniformLocations.count(_name) == 0) {
            std::cerr << "Get uniform: " << _name << " failed." << std::endl;
            return;
        }
        glUniformMatrix4fv(m_UniformLocations[_name], 1, false, _uniform.pointer());
    }

    void Shader::bind() const {
        glUseProgram(m_ProgramId);
    }
    void Shader::unbind() {
        glUseProgram(0);
    }
    bool Shader::isLoaded() const {
        return m_Loaded;
    }


    void Shader::createDefaultShaders() {
        const std::string vertexArray_Vertex = R"(
#version 410 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Color;

uniform mat4 model = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);

out vec4 fragColor;

void main() {
    gl_Position = projection * model * view * vec4(in_Position, 1.0);
    fragColor = in_Color;
})";
        const std::string vertexArray_Fragment = R"(
#version 410 core

in vec4 fragColor;
out vec4 FragColor;

void main() {
    FragColor = fragColor;
})";
        const std::string vertexArrayTexture_Vertex = R"(
#version 410 core

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec4 in_Color;
layout(location = 2) in vec2 in_TexUV;

uniform mat4 model = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);

out vec4 fragColor;
out vec2 texUV;

void main() {
    gl_Position = projection * view * model * vec4(in_Position, 1.0);
    fragColor = in_Color;
    texUV = in_TexUV;
})";
        const std::string vertexArrayTexture_Fragment = R"(
#version 410 core

in vec4 fragColor;
in vec2 texUV;

uniform sampler2D tex;
out vec4 FragColor;

void main() {
    FragColor = texture(tex, texUV) * fragColor;
})";

        VertexArrayShader.createShader(vertexArray_Vertex, vertexArray_Fragment, {"model", "view", "projection"});
        VertexArrayTextureShader.createShader(vertexArrayTexture_Vertex, vertexArrayTexture_Fragment, { "model", "view", "projection" });
    }
}
