#ifndef _OKA_TIMEMANAGER_H_
#define _OKA_TIMEMANAGER_H_

namespace oka
{
	class TimeManager
	{
	private:
		static TimeManager* m_instance;

	public:
		static TimeManager* GetInstance();
		unsigned int m_flame;

		void Update();
		int GetMilliSecond(const unsigned int _flame)const;
		int GetSecond(const unsigned int _flame)const;
		int GetMinutes(const unsigned int _second)const;

		TimeManager():
		m_flame(0)
		{}
	};
}

#endif