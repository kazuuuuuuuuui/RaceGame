#ifndef _OKA_MANAGER_H_
#define _OKA_MANAGER_H_

#include<map>
#include<string>
//#include<memory>
#include"GameObject.h"

#include"sequence.h"
#include"Character.h"
#include"glut.h"

namespace oka
{
	class GameManager
	{
	public:
		int m_flame;
		std::vector<GameObject*>m_gameObject;

		void Updata();
		void AddGameObject(GameObject *_object);

		static GameManager* GetInstance();

		// äeéÌÉVÅ[Éì
		void sceneTitle(float delta);
		void sceneCourseSelect(float delta);
		void scenePlay(float delta);
		Sequence< GameManager > _sequence;


	private:
		GameManager() :
			m_flame(0)
		{
			_sequence.change(&GameManager::sceneTitle);

		}
		~GameManager() {}

		static GameManager* m_instance;

	};
}

bool checkRanking(Character *_character1, Character *_character2);
extern unsigned int threeTexture;
extern unsigned int twoTexture;
extern unsigned int oneTexture;
extern unsigned int goTexture;
extern unsigned int goalTexture;
extern unsigned int rank1st;
extern unsigned int rank2nd;
extern unsigned int rank3rd;
extern unsigned int rank4th;

#endif