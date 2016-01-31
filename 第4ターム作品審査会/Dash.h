#pragma once

#define DASH_PARTICLE_NUMBER (10)

#include"Effect.h"
#include"Particle.h"
#include"glm\glm.hpp"

class Dash :public Effect{
public:
	Particle m_particle[DASH_PARTICLE_NUMBER];

	void draw();
	void update();
	
};

extern GLuint dash_handle;