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
	//�Q�[���̃I�u�W�F�N�g���Ǘ�����}�l�[�W���N���X

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
			printf("�Q�[���}�l�[�W���[����������܂���\n");
			printf("\n");

		}

		~GameManager()
		{
			//debug
			printf("�Q�[���}�l�[�W���[���폜����܂���\n");
			printf("\n");
		}

	};
}

bool checkRanking(Character *_character1, Character *_character2);

#endif