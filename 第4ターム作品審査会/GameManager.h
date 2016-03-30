#ifndef _OKA_MANAGER_H_
#define _OKA_MANAGER_H_

#include<map>
#include<string>
#include"GameObject.h"

#include"TitleScene.h"

#include"sequence.h"
#include"Character.h"
#include"glut.h"

namespace oka
{
	//----------------------------------------------
	//ゲームのオブジェクトを管理するマネージャクラス

	class GameManager
	{
	public:
		std::vector<GameObject*>m_gameObject;

		void Updata();
		void AddGameObject(GameObject *_object);
		void CheckGameObject();

		static GameManager* GetInstance();

		// 各種シーン
		//void sceneTitle(float delta);
		//void sceneCourseSelect(float delta);
		//void scenePlay(float delta);
		//Sequence< GameManager > _sequence;


	private:
		GameManager()
		{
			//_sequence.Change(&GameManager::sceneTitle);
		}
		static GameManager* m_instance;

	};
}

bool checkRanking(Character *_character1, Character *_character2);

#endif