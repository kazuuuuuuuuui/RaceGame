#pragma once

#include"Character.h"

class Enemy :public Character{
public:

	


	//�G��AI
	void control();

	Enemy(){
	

		//�p�x����̌����x�N�g��
		vv = { -sin(m_rotate.y), -cos(m_rotate.y) };
		v1 = vv;
	
	};



};
