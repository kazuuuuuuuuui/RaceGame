#pragma once

#include"Vec3.h"
#include"glm\glm.hpp"
#include"glut.h"

//-------------------------------------
//敵のAIのみに使用するためのレースフラッグの情報

class AimPoint
{
public:
	oka::Vec3 m_position;

	bool CheckPass(oka::Vec3 _position);

	AimPoint() :
		m_position(0, 0, 0)
	{}

};