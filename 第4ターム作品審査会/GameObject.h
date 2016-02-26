#pragma once

#include"transform.h"
#include"glm\glm.hpp"

//-------------------------------

class GameObject {

public:

	Transform transform;
	glm::vec3 m_speed;
	glm::vec3 m_accel;


	//���������X�g�Ŋe�����o������
	GameObject() :
		m_speed(0, 0, 0),
		m_accel(0, 0, 0)
	{};

	virtual void draw() = 0;
	virtual void update() = 0;
};

