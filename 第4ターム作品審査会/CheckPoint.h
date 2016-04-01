#ifndef CHECKPOINT_H_
#define CHECKPOINT_H_

#include"Vec3.h"
#include"glm\glm.hpp"
#include"glut.h"

//-------------------------------------
//周回に使用するためのチェックポイントの情報

class CheckPoint
{
public:
	oka::Vec3 m_position;

	bool CheckPass(oka::Vec3 _position);

	CheckPoint() :
		m_position(0, 0, 0)
	{}

};

#endif
