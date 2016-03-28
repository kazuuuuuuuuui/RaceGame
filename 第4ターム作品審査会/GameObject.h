#ifndef _OKA_GAMEOBJECT_H_
#define _OKA_GAMEOBJECT_H_

#include"Mat4×4.h"
#include"Transform.h"

//-------------------------------

namespace oka
{
	class GameObject {
	public:
		unsigned int m_flame;
		bool m_isActive;
		Mat4x4 m_matrix;
		Transform m_transform;
		Vec3 m_speed;
		Vec3 m_accel;

		bool CheckIsActive()const { return m_isActive; };

		//初期化リストで各メンバ初期化
		GameObject() :
			m_flame(0),
			m_isActive(true),
			m_matrix(Mat4x4::IndentityMatrix()),
			m_speed(0, 0, 0),
			m_accel(0, 0, 0)
		{};

		virtual void Draw() = 0;
		virtual void Update() = 0;
	};

}

#endif