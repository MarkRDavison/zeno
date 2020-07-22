#include <zeno/Game/ShaderManager.hpp>
#include <zeno/Utility/StringExtensions.hpp>
#include <iostream>
#include <cassert>

namespace ze {

	bool ShaderManager::createShader(const std::string& _shaderName) {
		return createShader(_shaderName, {});
	}
	bool ShaderManager::createShader(const std::string& _shaderName, const std::vector<std::string>& _uniformNames) {
		auto& s = getShader(_shaderName);
		if (s.createShader()) {
			for (const auto& u : _uniformNames) {
				if (!s.findLocationOfUniform(u)) {
					return false;
				}
			}
		}


		return true;
	}
	bool ShaderManager::loadShaderFiles(const std::string& _vertexPath, const std::string& _fragmentPath, const std::string& _shaderName) {
		auto shader = new Shader();
		if (!shader->loadShaderFiles(_vertexPath, _fragmentPath)) {
			delete shader;
			return false;
		}

		assert(m_Shaders.count(_shaderName) == 0);
		m_Shaders[_shaderName] = shader;
		return true;
	}
	bool ShaderManager::loadShader(const std::string& _vertexPath, const std::string& _fragmentPath, const std::string& _shaderName) {
		return loadShader(_vertexPath, _fragmentPath, _shaderName, {});
	}
	bool ShaderManager::loadShader(const std::string& _vertexPath, const std::string& _fragmentPath, const std::string& _shaderName, const std::vector<std::string>& _uniformNames) {
		const auto vertex = StringExtensions::loadFileToString(_vertexPath);
		const auto fragment = StringExtensions::loadFileToString(_fragmentPath);

		if (vertex.empty()) {
			std::cerr << "Could not find vertex shader file at '" << _vertexPath << "'" << std::endl;
			return false;
		}

		if (fragment.empty()) {
			std::cerr << "Could not find fragment shader file at '" << _fragmentPath << "'" << std::endl;
			return false;
		}

		auto shader = new Shader();
		if (!shader->createShader(vertex, fragment)) {
			delete shader;
			return false;
		}

		assert(m_Shaders.count(_shaderName) == 0);
		m_Shaders[_shaderName] = shader;

		for (const auto& u : _uniformNames) {
			if (!shader->findLocationOfUniform(u)) {
				return false;
			}
		}

		return true;
	}
	Shader& ShaderManager::getShader(const std::string& _shaderName) {
		assert(m_Shaders.count(_shaderName) > 0);
		return *((*m_Shaders.find(_shaderName)).second);
	}
	const Shader& ShaderManager::getShader(const std::string& _shaderName) const {
		assert(m_Shaders.count(_shaderName) > 0);
		return *((*m_Shaders.find(_shaderName)).second);
	}

}
