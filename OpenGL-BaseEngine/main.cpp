#include <stdio.h>
#include "Application.h"

int main() {
	Application* engine = new Application();

	engine->CreateEngine("Particle", 1280, 720);
	engine->Run();

	delete engine;
	return 0;
}