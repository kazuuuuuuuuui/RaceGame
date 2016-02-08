#pragma once

#include"Character.h"
#include"Smoke.h"
#include"Sound.h"




class Player :public Character{
public:

	Sound *m_engine;
	//	Sound *m_slip;

	//player‚Ì§Œä
	void control(unsigned int _pressedKey, unsigned int _downKeys, float _x, float _y, float _z);

	void printDashGauge();

	Player()
	{
		m_engine = new Sound();
		m_engine->loadKukeiha(engine_sound, sizeof(engine_sound), 110);
		m_engine->changeVolume(0.3f);

		/*	m_slip = new Sound();
			m_slip->loadWavFile("");*/

	}
};

extern Player *player;
extern GLuint dashIcon;
extern GLuint dashGauge;