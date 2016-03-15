#pragma once

#include"GameObject.h"
#include"glm\glm.hpp"
#include"glut.h"

class Particle :public oka::GameObject{
public:

	float m_alpha;

	void draw(){};
	void draw(int _type,glm::vec3 _color,GLuint _texture);
	void update(){};

	Particle() :
		m_alpha(0.f)
	{}
};