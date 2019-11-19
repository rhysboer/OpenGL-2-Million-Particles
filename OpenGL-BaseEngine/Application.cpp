#include "Application.h"

void Application::OnStart() {
	ShaderManager::InitShaders();

	this->camera = new Camera(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0, 1.0f, 0.0f), -90.0f, 0.0f, glm::radians(40.0f), 0.25f, 4000.0f);
	unsigned int max = 1048576 * 2;

	this->particles = new ParticleSystem(max);
}

void Application::OnUpdate() {
	this->camera->InputHandler();
}

void Application::OnRender() {
	particles->Render(*camera);
}

void Application::OnEnd() {
}

