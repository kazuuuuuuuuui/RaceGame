#ifndef _OKA_GAMEOBJECT_H_
#define _OKA_GAMEOBJECT_H_

#include"transform.h"

//-------------------------------

namespace oka
{
	class GameObject {

	public:
		Transform transform;
		Vec3 m_speed;
		Vec3 m_accel;


		//���������X�g�Ŋe�����o������
		GameObject() :
			m_speed(0, 0, 0),
			m_accel(0, 0, 0)
		{};

		virtual void draw() = 0;
		virtual void update() = 0;
	};

}

#endif