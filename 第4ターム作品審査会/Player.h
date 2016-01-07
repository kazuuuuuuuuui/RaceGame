#pragma once

#include"FlyingObject.h"

//-------------------------------------
//©‹@‚Ìî•ñ

class Player :public FlyingObject{
public:

	void draw();
	void update();
	void control(unsigned int _key, float _x, float _y, float _z);
	bool inDart();

	//Œã‚Å‘‚«Š·‚¦‚é
	Player(){
		m_position.x = 22.f;
		m_position.y = 0.01f;
		m_position.z = -68.f;
	}

};

extern Player *player;