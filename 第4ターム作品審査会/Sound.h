#pragma once

#include<stdio.h>
#include"AL\al.h"
#include"AL\alc.h"

namespace oka
{
	class Sound
	{
	public:
		static unsigned int LoadSquareWave(const unsigned char *data, int _size, int _freq);
		static unsigned int LoadWavFile(const char *_wavFileName);
		static void Play(unsigned int _sound);
		static void Stop(unsigned int _sound);
	};

}

extern unsigned char engine_sound[8];
extern unsigned char count_sound[8];

