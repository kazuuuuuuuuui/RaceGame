#ifndef BASESCENE_H_
#define BASESCENE_H_

//--------------------------
//あらゆるシーンの基底クラス

class BaseScene
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	BaseScene() {};
	virtual ~BaseScene() {};
};

#endif