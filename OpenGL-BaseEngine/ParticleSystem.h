#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <vector>

#include "ShaderManager.h"
#include "Camera.h"

/* 
	Dedicated to my dog Bonnie
	2004 - 2019
*/ 

class ParticleSystem {
public:
	ParticleSystem(unsigned int& maxParticles);
	~ParticleSystem() {}

	void Render(Camera& camera);

private:
	static const float VERTEX_DATA[];

	std::vector<glm::vec3> GetPointsAroundSphere(unsigned int& num);

	Shader* shader_g; // Graphics
	Shader* shader_c; // Compute

	unsigned int VAO;
	unsigned int VBO;

	unsigned int particle_pos;
	unsigned int particle_vel;

	unsigned int totalParticles;
};

