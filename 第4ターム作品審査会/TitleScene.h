#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include<stdio.h>
#include"BaseScene.h"

//--------------------
//タイトルシーンクラス

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
		printf("タイトルシーン生成\n");
	};

	~TitleScene()
	{
		//debug
		printf("タイトルシーン削除\n");
	};
};

#endif
