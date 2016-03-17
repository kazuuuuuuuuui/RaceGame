#ifndef _OKA_SOUNDMANAGER_H_
#define _OKA_SOUNDMANAGER_H_

#include<map>
#include<string>
#include"Sound.h"

namespace oka
{
	//-------------------------------------
	//ゲーム中で使用する音を管理すすクラス

	class SoundManager
	{
	private:
		static SoundManager* m_instance;
		
		void init();
		SoundManager() { SoundManager::init(); }
		~SoundManager() {}

	public:
		std::map<std::string, unsigned int>m_sounds;
		static SoundManager* getInstance();
		void AddSound(const std::string _str, unsigned int _sound);
		void DeleteSound(const std::string _str);
		void Play(const std::string _str);
		void Stop(const std::string _str);
		void ChangeVolume(const std::string _str,const float _value);
		void ChangePitch(const std::string _str, const float _value);
	};

}

#endif