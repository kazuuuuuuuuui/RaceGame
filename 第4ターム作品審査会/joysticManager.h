#ifndef _OKA_JOYSTICK_MANAGER_
#define _OKA_JOYSTICK_MANAGER_

#include<vector>
#include"Controller.h"
#include"Character.h"

namespace oka
{
	class JoysticManager
	{
	private:
		static JoysticManager* m_instance;
		std::vector<Contoroller>m_contoroller;

		JoysticManager() {};

	public:
		Contoroller GetContoroller(const int _num)const;
		void AddController(Contoroller _Contoroller);
		unsigned int GetConnectingNum()const;
		void Update();
		static JoysticManager* GetInstance();
	};

}

#endif