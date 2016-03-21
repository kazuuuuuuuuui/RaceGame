#include<stdio.h>
#include"JoysticManager.h"

namespace oka
{
	JoysticManager* JoysticManager::m_instance = nullptr;

	//-------------------------------------------------------------------------------------------------------
	//ジョイスティックのインスタンス取得

	JoysticManager* JoysticManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new JoysticManager();
		}

		return m_instance;
	}


	//-------------------------------------
	//キャラクターとコントローラの対応付け
	//引数としてキャラクタ型のポインタを受け取り
	//コントローラを管理しているベクターに入れる

	void JoysticManager::AddController(Contoroller _character)
	{
		m_contoroller.push_back(_character);
	}

	//-------------------------------------
	//現在繋がっているコントローラーの台数を返す

	unsigned int JoysticManager::GetConnectingNum()const
	{
		return m_contoroller.size();
	}



	Contoroller JoysticManager::GetContoroller(const int _num)const
	{
		if (0 != this->GetConnectingNum())
		{
			return m_contoroller[_num];
		}
		else
		{
			
		}
	}

	//-------------------------------------
	//コントローラーが繋がっているかのチェックと
	//現在繋がっているコントローラーの台数チェック

	void JoysticManager::Update()
	{
		for (unsigned int i = 0; i < m_contoroller.size(); i++)
		{
			if (ERROR_SUCCESS == XInputGetState(i, &m_contoroller[i].m_state))
			{
				m_contoroller[i].m_isConnect = true;
				m_contoroller[i].Update();
			}
			else
			{
				m_contoroller[i].m_isConnect = false;
			}

		}

	}



}