#pragma once
#include "Engine.h"
#include "Camera.h"

#include "ParticleSystem.h"
#include "ShaderManager.h"

class Application : public Engine {
public:

private:

	virtual void OnStart() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnEnd() override;

	Camera* camera;

	ParticleSystem* particles;

};

