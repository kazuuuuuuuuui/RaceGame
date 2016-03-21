#pragma once

#include"GameObject.h"
#include"glm\glm.hpp"
#include"glut.h"

class Particle :public oka::GameObject{
public:

	float m_alpha;

	void Draw(){};
	void Draw(int _type,glm::vec3 _color,unsigned int _texture);
	void Update(){};

	Particle() :
		m_alpha(0.f)
	{}
};