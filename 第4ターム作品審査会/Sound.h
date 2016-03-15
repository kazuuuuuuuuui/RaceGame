#pragma once

#include<stdio.h>
#include"AL\al.h"
#include"AL\alc.h"

class Sound{
public:

	ALuint m_bid;
	ALuint m_sid;

	static void init();
	void play();
	void stop();
	void loadKukeiha(const unsigned char *data, int _size, ALsizei _freq);
	void loadWavFile(const char *_wavFileName);
	void checkState();
	void changeVolume(float _value);

	Sound() :
		m_bid(0),
		m_sid(0)
	{}
	Sound(const char *_wavFilename) { loadWavFile(_wavFilename); }

	~Sound(){ printf("Œø‰Ê‰¹‚ªíœ‚³‚ê‚Ü‚µ‚½\n"); };

};

extern unsigned char engine_sound[8];
extern unsigned char count_sound[8];

extern Sound *startCountDown;
