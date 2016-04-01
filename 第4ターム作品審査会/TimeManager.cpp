#include"TimeManager.h"

namespace oka
{
	TimeManager* TimeManager::m_instance = nullptr;

	//-----------------------------------------------
	//タイムマネージャのインスタンス取得

	TimeManager* TimeManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new TimeManager();
		}

		return m_instance;
	}

	//------------------------
	//タイムマネージャーの更新

	void TimeManager::Update()
	{
		m_flame++;
	}

	int TimeManager::GetMilliSecond(const unsigned int _flame)const
	{
		return ((_flame * 1000) / 60) % 1000;
	}

	int TimeManager::GetSecond(const unsigned int _flame)const
	{
		return _flame / 60;
	}

	int TimeManager::GetMinutes(const unsigned int _second)const
	{
		unsigned int minute = _second / 60;

		return minute;
	}

}