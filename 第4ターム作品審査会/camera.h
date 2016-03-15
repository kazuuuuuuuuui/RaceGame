#ifndef _OKA_CAMERA_H_
#define _OKA_CAMERA_H_

#include"Vec3.h"
#include"glm\glm.hpp"

enum {
	TYPE_2D,
	TYPE_3D
};

namespace oka 
{
	class Camera
	{
	public:
		double m_angle;
		double m_aspect;
		double m_zNear;
		double m_zFar;
		Vec3 m_position;
		Vec3 m_rotate;
		Vec3 m_target;
		Vec3 m_up;

		Camera() :
			m_angle(60),
			m_aspect(1),
			m_zNear(0.1),
			m_zFar(1000),
			m_position(0, 0, 0),
			m_rotate(0, 0, 0),
			m_target(0, 0, 10),
			m_up(0, 1, 0)
		{};

		void update(const int _type);
		void SetPosition(Vec3 _position) { m_position = _position; }
		void SetTarget(Vec3 _target) { m_target = _target; }

	};

}//namespace oka

extern oka::Camera *g_camera;

#endif

