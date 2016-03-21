#pragma once

#define DASH_PARTICLE_NUMBER (10)

#include"Effect.h"
#include"Particle.h"
#include"glm\glm.hpp"

class Dash :public Effect{
public:
	Particle m_particle[DASH_PARTICLE_NUMBER];

	void Draw();
	void Update();
	
};

extern unsigned int dash_handle;