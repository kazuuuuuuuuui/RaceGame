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
		static void Destroy();

	private:
		static GameManager* m_instance;

		GameManager()
		{
			//debug
			printf("ゲームマネージャーが生成されました\n");
			printf("\n");

		}

		~GameManager()
		{
			//debug
			printf("ゲームマネージャーが削除されました\n");
			printf("\n");
		}

	};
}

bool checkRanking(Character *_character1, Character *_character2);

#endif