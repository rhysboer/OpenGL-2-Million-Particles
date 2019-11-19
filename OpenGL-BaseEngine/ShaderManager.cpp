#include "ShaderManager.h"

std::map<const char*, Shader> ShaderManager::graphicShaders = std::map<const char*, Shader>();
std::map<const char*, Shader> ShaderManager::computeShaders = std::map<const char*, Shader>();

void ShaderManager::InitShaders() {
	AddShader("particle");
	AddShader("particle", ShaderType::COMPUTE);
}

Shader* ShaderManager::GetShader(const char* name, ShaderType type) {
	if(type == ShaderType::GRAPHIC) {
		std::map<const char*, Shader>::iterator iter = graphicShaders.find(name);
		if(iter != graphicShaders.end())
			return &(*iter).second;
	}else if(type == ShaderType::COMPUTE) {
		std::map<const char*, Shader>::iterator iter = computeShaders.find(name);
		if(iter != computeShaders.end())
			return &(*iter).second;
	} else {
		printf("GetShader() : Failed to find shader type: %i\n", type);
		return nullptr;
	}

	printf("GetShader() : Failed to find shader: %s!\n", name);
	return nullptr;
}

void ShaderManager::AddShader(const char* fileNames, ShaderType type) {
	std::string path = PATH;
	std::ifstream file;

	if(type == ShaderType::GRAPHIC) {
		// Vertex
		file.open(path + fileNames + ".vert");

		if(!file.is_open()) {
			printf("Failed to load Vertex Shader: %s", fileNames);
			file.close();
			return;
		}

		std::string vertSource((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();

		// Fragment
		file.open(path + fileNames + ".frag");

		if(!file.is_open()) {
			printf("Failed to load Fragment Shader: %s", fileNames);
			file.close();
			return;
		}

		std::string fragSource((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();

		Shader shader = Shader();
		if(shader.LoadShader(vertSource, fragSource)) {
			graphicShaders.insert(std::pair<const char*, Shader>(fileNames, shader));
		}
	} else {
		file.open(path + fileNames + ".comp");

		if(!file.is_open()) {
			printf("Failed to load Compute Shader: %s", fileNames);
			file.close();
			return;
		}

		std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();

		Shader shader = Shader();
		if(shader.LoadShader(source)) {
			computeShaders.insert(std::pair<const char*, Shader>(fileNames, shader));
		}
	}
}
