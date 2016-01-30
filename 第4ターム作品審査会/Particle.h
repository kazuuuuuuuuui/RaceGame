#pragma once

#include"GameObject.h"
#include"glm\glm.hpp"

class Particle :public GameObject{
public:

	float m_alpha;

	void draw(){};
	void draw(glm::vec3 _color);
	void update(){};

	Particle() :
		m_alpha(0.f)
	{}
};