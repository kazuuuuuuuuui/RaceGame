#pragma once

#include"Character.h"

class Enemy :public Character{
public:

	void control();
	void useItem();

	Enemy(){
	
		//角度からの向きベクトル
		OrientationVector = { -sin(m_rotate.y), -cos(m_rotate.y) };
		m_pos_to_AIpoint = OrientationVector;
	
	};
};

extern Enemy *com1;
extern Enemy *com2;
extern Enemy *com3;