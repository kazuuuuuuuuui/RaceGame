#pragma once

#include<list>
#include"GameObject.h"
#include"glut.h"

class Effect :public oka::GameObject
{
public:
	bool m_isActive;

	oka::Vec3 m_basePosition;

	void checkCourseOut();
	virtual void draw() = 0;
	virtual void update() = 0;

	Effect() :
		m_isActive(false),
		m_basePosition(0, 0, 0)
	{}
};

extern std::list<Effect*>effect;

extern unsigned int smoke_handle;
extern unsigned int EffectBlizzard;