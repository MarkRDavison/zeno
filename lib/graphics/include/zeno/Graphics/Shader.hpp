#ifndef INCLUDED_ZENO_GRAPHICS_SHADER_HPP_
#define INCLUDED_ZENO_GRAPHICS_SHADER_HPP_

#include <string>
#include <map>
#include <zeno/Core/Vector2.hpp>
#include <zeno/Core/Vector3.hpp>
#include <zeno/Core/Vector4.hpp>
#include <zeno/Core/Mat4x4.hpp>
#include <zeno/Graphics/Colour.hpp>

namespace ze {

    class Shader {
    public:
        ~Shader();


        bool loadShaderFiles(const std::string& _vertex, const std::string& _fragment);
        bool createShader();

        bool createShader(const std::string& _vertex, const std::string& _fragment);

        bool findLocationOfUniform(const std::string& _uniform);
        void passUniform(const std::string& _name, float _uniform);
        void passUniform(const std::string& _name, const Vector2<float>& _uniform);
        void passUniform(const std::string& _name, const Vector3<float>& _uniform);
        void passUniform(const std::string& _name, const Vector4<float>& _uniform);
        void passUniform(const std::string& _name, const Colour& _uniform);
        void passUniform(const std::string& _name, const Mat4x4& _uniform);

        bool isLoaded() const;

        void bind() const;
        static void unbind();

    private:
        bool m_Loaded{ false };
        unsigned m_ProgramId{ 0u };
        std::map<std::string, int> m_UniformLocations;
        std::string m_VertexSource;
        std::string m_FragmentSource;
    };

}

#endif // INCLUDED_ZENO_GRAPHICS_SHADER_HPP_