#pragma once

#include"Character.h"

class Enemy :public Character{
public:

	


	//敵のAI
	void control();

	Enemy(){
	

		//角度からの向きベクトル
		vv = { -sin(m_rotate.y), -cos(m_rotate.y) };
		v1 = vv;
	
	};



};
