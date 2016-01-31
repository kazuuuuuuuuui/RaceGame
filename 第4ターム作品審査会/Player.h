#pragma once

#include"Character.h"
#include"Smoke.h"

class Player :public Character{
public:


	//player‚Ì§Œä
	void control(unsigned int _pressedKey, unsigned int _downKeys, float _x, float _y, float _z);

	void printDashGauge();
};

extern Player *player;
extern GLuint dashIcon;
extern GLuint dashGauge;