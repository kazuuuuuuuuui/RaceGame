#pragma once

#include"Vec3.h"
#include"glm\glm.hpp"
#include"glut.h"

//-------------------------------------
//�G��AI�݂̂Ɏg�p���邽�߂̃��[�X�t���b�O�̏��

class AIFlag{
public:
	oka::Vec3 m_position;

	void draw();
	bool checkPassFlag(oka::Vec3 _position);

	AIFlag() :
		m_position(0, 0, 0)
	{}

};