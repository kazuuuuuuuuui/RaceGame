#pragma once

#include"glm\glm.hpp"
#include"glut.h"

//-------------------------------------
//�G��AI�݂̂Ɏg�p���邽�߂̃��[�X�t���b�O�̏��

class AIFlag{
public:
	glm::vec3 m_position;

	void draw();
	bool checkPassFlag(glm::vec3 _position);

	AIFlag() :
		m_position(0, 0, 0)
	{}

};