#ifndef BIKEWHEEL_H_
#define BIKEWHEEL_H_

#include"GameObject.h"
#include"xFile.h"

class BikeWheel :public oka::GameObject
{
public:
	xFile m_model;
	
	void Update() {};
	void Draw();
	BikeWheel()
	{
		m_transform.SetScale(oka::Vec3(0.9f, 0.9f, 0.9f));
	}

};

#endif