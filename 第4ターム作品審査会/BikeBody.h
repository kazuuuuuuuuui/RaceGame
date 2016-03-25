#ifndef BIKEBODY_H_
#define BIKEBODY_H_

#include"GameObject.h"
#include"xFile.h"

class BikeBody :public oka::GameObject
{
public:
	xFile m_model;

	void Update(){};
	void Draw();
	void DrawShadow();
	BikeBody() {};

};


#endif
