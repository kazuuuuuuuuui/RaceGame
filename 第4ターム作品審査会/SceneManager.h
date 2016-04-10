#ifndef OKA_SCENEMANAGER_H_
#define OKA_SCENEMANAGER_H_

#include"Sequence.h"
#include"BaseScene.h"
#include"TitleScene.h"

/*

Ç±Ç±ÇÃçlÇ¶ï˚Ç™Ç¢Ç‹Ç¢ÇøÇÌÇ©ÇÁÇ»Ç¢

*/


namespace oka
{
	class SceneManager
	{
	public:
		void Update();
		Sequence<SceneManager> m_sequence;
		BaseScene *m_nowScene;
		BaseScene *m_prevScene;


		static SceneManager* GetInstance();

	private:
		static SceneManager* m_instance;

		void Title(float _delta);
		void CourseSelect(float _delta);
		void GameMain(float _delta);
		void Pause(float _delta);
		 
		SceneManager();		

	};
}

#endif