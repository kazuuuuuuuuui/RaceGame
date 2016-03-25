#pragma once

#include"Vec3.h"
#include"glm\glm.hpp"
#include"glut.h"

void Circle2D(float radius, int x, int y);

//-------------------------------------
//周回に使用するためのレースフラッグの情報

class CourseFlag{
public:
	oka::Vec3 m_position;

	void draw();
	bool checkPassFlag(oka::Vec3 _position);

	CourseFlag() :
		m_position(0, 0, 0)
	{}

};

//debug
void Circle2D(float radius, int x, int y);
