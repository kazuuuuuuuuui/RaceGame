#pragma once

#include"Character.h"

class Player :public Character{
public:


	//player�̐���
	void control(unsigned int _pressedKey, unsigned int _downKeys, float _x, float _y, float _z);


};

extern Player *player;