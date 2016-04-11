//debug
#include<iostream>

#include<assert.h>
#include"SoundManager.h"

namespace oka
{
	SoundManager* SoundManager::m_instance = nullptr;
	
	//-------------------------------------
	//ALの初期化処理
	//デバイスの取得とコンテキストの作成をする

	void SoundManager::init()
	{
		ALCdevice *device = alcOpenDevice(NULL);
		assert(alcGetError(device) == ALC_NO_ERROR);

		ALCcontext *context;
		context = alcCreateContext(device, NULL);
		assert(alcGetError(device) == ALC_NO_ERROR);

		alcMakeContextCurrent(context);
		assert(alcGetError(device) == ALC_NO_ERROR);
	}


	//--------------------------------------------
	//シングルトンにするためにインスタンスが
	//生成されていなければインスタンスを生成し
	//既にインスタンスが生成されていればそのインスタンスを返す

	SoundManager* SoundManager::GetInstance() {

		if (nullptr == m_instance) 
		{
			m_instance = new SoundManager();
		}
		return m_instance;
	}

	//-------------------------------------
	//文字列keyとSound型のvalueを受け取って
	//メンバのmapに既に登録されているかチェックし
	//登録されていなければ追加する

	void SoundManager::AddSound(const std::string _str, unsigned int _sound)
	{
		if (m_sounds.find(_str)==m_sounds.end())
		{
			//debug
			std::cout << "*Sound " << _str << "を追加しました\n";

			m_sounds.insert(std::make_pair(_str, _sound));
		}
		else
		{
			
		}
	}

	//-------------------------------------
	//引数として受け取ったkeyがmapに登録されているか
	//検索し登録されていればそのkeyに対応するテクスチャハンドルを返す

	unsigned int SoundManager::GetHandle(const std::string _str)const
	{
		if (m_sounds.find(_str) == m_sounds.end())
		{
			//要修正
			return 0;
		}
		else
		{
			return m_sounds.find(_str)->second;
		}
	}


	//-------------------------------------
	//文字列keyとSound型のvalueを受け取って
	//メンバのmapに既に登録されているかチェックし
	//登録されていればmapから除外しdeleteする

	//使うとき要注意

	void SoundManager::DeleteSound(const std::string _str)
	{
		if (m_sounds.find(_str) == m_sounds.end())
		{
			
		}
		else
		{
			//debug
			std::cout << "*Sound " << _str << "は削除されました\n";

			m_sounds.erase(_str);
		}
	}

	//-------------------------------------
	//音の再生

	void SoundManager::Play(const std::string _str)
	{
		if (m_sounds.find(_str) == m_sounds.end())
		{
	
		}
		else
		{
			alSourcePlay(m_sounds[_str]);
		}
	}


	//-------------------------------------
	//音の停止

	void SoundManager::Stop(const std::string _str)
	{
		if (m_sounds.find(_str) == m_sounds.end())
		{

		}
		else
		{
			alSourceStop(m_sounds[_str]);
		}
		
	}

	//-------------------------------------
	//音量の調整

	void SoundManager::ChangeVolume(const std::string _str,const float _value)
	{
		alSourcef(m_sounds[_str], AL_GAIN, _value);

	}

	//-------------------------------------
	//音階の変更
	void SoundManager::ChangePitch(const std::string _str, const float _value)
	{
		alSourcef(m_sounds[_str], AL_PITCH, _value);

	}

}//namespace oka