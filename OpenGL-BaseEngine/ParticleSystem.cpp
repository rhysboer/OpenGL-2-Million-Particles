#include "ParticleSystem.h"

const float ParticleSystem::VERTEX_DATA[] = { 
	-0.5f,-0.5f, 0.0f,
	 0.5f,-0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f,
	 0.5f, 0.5f, 0.0f,
};

ParticleSystem::ParticleSystem(unsigned int& maxParticles) {
	this->totalParticles = maxParticles;
	this->shader_g = ShaderManager::GetShader("particle");
	this->shader_c = ShaderManager::GetShader("particle", ShaderManager::ShaderType::COMPUTE);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, VERTEX_DATA, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glVertexAttribDivisor(0, 0);
	
	std::vector<glm::vec3> pos = GetPointsAroundSphere(maxParticles);

	std::vector<glm::vec4> particlePosition = std::vector<glm::vec4>();
	std::vector<glm::vec4> particleVelocity = std::vector<glm::vec4>();
	particlePosition.reserve(maxParticles);
	particleVelocity.reserve(maxParticles);

	for(int i = 0; i < maxParticles; i++) {
		particlePosition.push_back(glm::vec4(pos[i] * 25.0f, 0.0f));
		particleVelocity.push_back(glm::vec4(0.0f));
	}

	// Generate Shader Storage
	glGenBuffers(1, &particle_pos);
	glGenBuffers(1, &particle_vel);

	// Position
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, particle_pos);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec4) * maxParticles, &particlePosition[0], GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, particle_pos);

	// Velocity
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, particle_vel);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec4) * maxParticles, &particleVelocity[0], GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, particle_vel);
}

void ParticleSystem::Render(Camera& camera) {
	glBindVertexArray(VAO);

	shader_c->UseProgram();
	shader_c->SetVector3("origin", Camera::ActiveCamera->Position() + (Camera::ActiveCamera->Forward() * 150.0f));
	shader_c->SetFloat("deltaTime", Time::DeltaTime());
	shader_c->SetInt("isActive", Input::IsMouseKeyDown(GLFW_MOUSE_BUTTON_LEFT));
	glDispatchCompute(totalParticles / 64, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

	shader_g->UseProgram();
	shader_g->SetMatrix4("projection", camera.ProjectionView());
	shader_g->SetVector3("camRight", camera.Right());
	shader_g->SetVector3("camUp", camera.Up());

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, totalParticles);
}

std::vector<glm::vec3> ParticleSystem::GetPointsAroundSphere(unsigned int& num) {
	std::vector<glm::vec3> points = std::vector<glm::vec3>();
	points.reserve(num);

	const double PI = 3.14159265359;
	float inc = PI * (3 - glm::sqrt(5));
	float off = 2.0f / num;
	float x = 0;
	float y = 0;
	float z = 0;
	float r = 0;
	float phi = 0;

	for(int k = 0; k < num; k++) {
		y = k * off - 1 + (off / 2);
		r = glm::sqrt(1 - y * y);
		phi = k * inc;
		x = glm::cos(phi) * r;
		z = glm::sin(phi)* r;

		points.push_back(glm::vec3(x, y, z));
	}

	return points;
}
