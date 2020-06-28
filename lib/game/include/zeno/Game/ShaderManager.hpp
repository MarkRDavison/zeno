#ifndef INCLUDED_ZENO_GAME_SHADER_MANAGER_HPP_
#define INCLUDED_ZENO_GAME_SHADER_MANAGER_HPP_

#include <zeno/Graphics/Shader.hpp>
#include <vector>
#include <map>

namespace ze {

	class ShaderManager {
	public:
		bool createShader(const std::string& _shaderName);
		bool createShader(const std::string& _shaderName, const std::vector<std::string>& _uniformNames);
		bool loadShaderFiles(const std::string& _vertexPath, const std::string& _fragmentPath, const std::string& _shaderName);
		bool loadShader(const std::string& _vertexPath, const std::string& _fragmentPath, const std::string& _shaderName);
		Shader& getShader(const std::string& _shaderName);
		const Shader& getShader(const std::string& _shaderName) const;

	private:
		std::map<std::string, Shader*> m_Shaders;
	};

}

#endif // INCLUDED_ZENO_GAME_SHADER_MANAGER_HPP_