#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include"BaseScene.h"

//--------------------
//タイトルシーンクラス

class TitleScene:public BaseScene
{
public:

	enum Mode
	{
		Single = 0,
		Vs,
		Max
	};

	int m_mode;

	void Update();
	void Render();

	TitleScene():
	m_mode(Single)
	{}
};

#endif
