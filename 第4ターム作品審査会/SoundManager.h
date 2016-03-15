#pragma once

#include<stdio.h>
#include<map>
#include<string>
#include"Sound.h"

class SoundManager {

public:

	std::map<std::string, Sound*>m_sounds;

	~SoundManager() {}
	void updata();
	static SoundManager* getInstance();
	void addSound(const std::string _str, Sound *_sound);

private:
	SoundManager() {
	
		Sound::init();

		//debug
		printf("サウンドマネージャーが生成されました\n");

	}
	
	static SoundManager* m_instance;

};