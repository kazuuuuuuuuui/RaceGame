#pragma once

#include<list>
#include"GameObject.h"
#include"glut.h"

class Effect :public oka::GameObject
{
public:
	oka::Vec3 m_basePosition;

	void checkCourseOut();
	virtual void Draw() = 0;
	virtual void Update() = 0;

	Effect() :
		m_basePosition(0, 0, 0)
	{
		m_isActive = false;
	}
};
