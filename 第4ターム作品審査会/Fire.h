#pragma once

#define FIRE_PARTICLE_NUMBER (30)

#include"Effect.h"
#include"Particle.h"
#include"glm\glm.hpp"

class Fire :public Effect{
public:
	Particle m_particle[FIRE_PARTICLE_NUMBER];
	

	void Draw();
	void Update();
	bool isHit(oka::Vec3 _position);

};

