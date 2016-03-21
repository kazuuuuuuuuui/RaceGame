#pragma once

#define SMOKE_PARTICLE_NUMBER (10)

#include"Effect.h"
#include"Particle.h"

class Smoke :public Effect{
public:
	Particle m_particle[SMOKE_PARTICLE_NUMBER];

	void Draw();
	void Update();
};
