#pragma once

#define FIRE_PARTICLE_NUMBER (30)

#include"Effect.h"
#include"Particle.h"
#include"glm\glm.hpp"

class Fire :public Effect{
public:
	Particle m_particle[FIRE_PARTICLE_NUMBER];
	

	void draw();
	void update();
	bool isHit(glm::vec3 _position);

};

extern GLuint smoke_handle;