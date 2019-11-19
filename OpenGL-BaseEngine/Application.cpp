#include "Application.h"

void Application::OnStart() {
	ShaderManager::InitShaders();

	this->camera = new Camera(glm::vec3(0.0f, 0.0f, 100.0f), glm::vec3(0.0, 1.0f, 0.0f), -90.0f, 0.0f, glm::radians(40.0f), 0.25f, 4000.0f);

	unsigned int totalParticles = 1048576 * 2;
	this->particles = new ParticleSystem(totalParticles);

	this->shader = ShaderManager::GetShader("reticle");
	this->crosshairActive = true;

	float vertices[] = {
		0.0f, 0.5f, 0.0f,
		0.0f,-0.5f, 0.0f,
		0.5f, 0.0f, 0.0f,
	   -0.5f, 0.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
}

void Application::OnUpdate() {
	this->camera->InputHandler();

	if(Input::IsKeyPressed(GLFW_KEY_F1))
		crosshairActive = !crosshairActive;
}

void Application::OnRender() {
	particles->Render(*camera);

	if(crosshairActive) {
		shader->UseProgram();
		shader->SetMatrix4("projection", Camera::ActiveCamera->Projection());
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, 4);
	}
}

void Application::OnEnd() {
	delete camera;
	delete particles;
}

