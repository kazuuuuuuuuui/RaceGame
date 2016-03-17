#ifndef T2K_GAME_MANAGER_H
#define T2K_GAME_MANAGER_H

#include"sequence.h"
#include"Character.h"
#include"glut.h"

class GameManager {

public:
	int m_flame;

	~GameManager() {}
	void updata();

	// ŠeíƒV[ƒ“
	void sceneTitle(float delta);
	void sceneCourseSelect(float delta);
	void scenePlay(float delta);

	static GameManager* getInstance();

	Sequence< GameManager > _sequence;


private:
	GameManager():
		m_flame (0)
	{
		_sequence.change(&GameManager::sceneTitle);

	}

	static GameManager* m_instance;

};



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
