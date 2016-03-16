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

	// 各種シーン
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

		//debug
		printf("ゲームマネージャーが生成されました\n");
	}

	static GameManager* m_instance;

};



bool checkRanking(Character *_character1, Character *_character2);
extern GLuint threeTexture;
extern GLuint twoTexture;
extern GLuint oneTexture;
extern GLuint goTexture;
extern GLuint goalTexture;
extern GLuint rank1st;
extern GLuint rank2nd;
extern GLuint rank3rd;
extern GLuint rank4th;



#endif
