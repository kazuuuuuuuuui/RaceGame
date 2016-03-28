#include"ScreenManager.h"
#include"glut.h"

namespace oka
{
	ScreenManager* ScreenManager::m_instance = nullptr;

	//-------------------------------------------------------------------------------------------------------
	//スクリーンマネージャのインスタンス取得

	ScreenManager* ScreenManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new ScreenManager();
		}

		return m_instance;
	}

	//-------------------------------------
	//ビューポートの設定

	void ScreenManager::SetViewport(const int _x, const int _y, const int _width, const int _height)const
	{
		glViewport(_x, _y, _width, _height);
	}

}