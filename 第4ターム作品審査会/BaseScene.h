#ifndef BASESCENE_H_
#define BASESCENE_H_

//--------------------------
//������V�[���̊��N���X

class BaseScene
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	BaseScene() {};
	virtual ~BaseScene() {};
};

#endif