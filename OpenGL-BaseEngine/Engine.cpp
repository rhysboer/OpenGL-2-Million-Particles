#include "Engine.h"
#include <string>

GLFWwindow* Engine::window = nullptr;

void _CallbackFrameBufferResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

bool Engine::CreateEngine(const char* title, const int& width, const int& height) {
	if(!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(width, height, title, NULL, NULL);
	
	if(!this->window) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(this->window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		return false;
	}

	glViewport(0, 0, width, height);
	InitCallbacks();
	this->isInitialized = true;

	// Call On Start
	OnStart();

	return true;
}

void Engine::Run() {
	if(!isInitialized)
		return;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	Init();

	while(!glfwWindowShouldClose(this->window)) {
		Time::Update();

		std::string title = "Particle Demo ms: " + std::to_string(Time::DeltaTime());
		title += " fps: " + std::to_string(1.0f / Time::DeltaTime());
		glfwSetWindowTitle(window, title.c_str());

		OnUpdate();

		Input::Update();
		
		glClearColor(this->colourBackground.r, this->colourBackground.g, this->colourBackground.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		OnRender();

		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}

	OnEnd();

	glfwTerminate();
}

glm::ivec2 Engine::GetWindowSize() {
	glm::ivec2 size = glm::ivec2(0.0f);
	if(!window) return size;

	glfwGetWindowSize(window, &size.x, &size.y);
	return size;
}


// Private Functions

Engine::Engine() {
	this->isInitialized = false;
	this->window = nullptr;
	this->colourBackground = glm::vec3(0.0f);
}

glm::ivec2 Engine::WindowSize() const {
	glm::ivec2 size;
	glfwGetWindowSize(this->window, &size.x, &size.y);
	return size;
}

void Engine::Init() {
}

void Engine::InitCallbacks() {
	Input::SetCallbacks(this->window);
	glfwSetFramebufferSizeCallback(this->window, _CallbackFrameBufferResize);
}
