#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include<stdio.h>
#include"BaseScene.h"

//--------------------
//�^�C�g���V�[���N���X

class TitleScene:public BaseScene
{
public:

	enum GameMode
	{
		single = 0,
		vs,
		exit,
		GameModeMax
	};

	static int m_gameMode;
	static const char *m_gameModeName[GameModeMax];

	void Update();
	void Render();

	TitleScene() 
	{
		//debug
		printf("�^�C�g���V�[������\n");
	};

	~TitleScene()
	{
		//debug
		printf("�^�C�g���V�[���폜\n");
	};
};

#endif
