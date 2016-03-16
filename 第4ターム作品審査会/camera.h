#ifndef _OKA_CAMERA_H_
#define _OKA_CAMERA_H_

#include"Vec3.h"
#include"Mat4Å~4.h"
#include"glm\glm.hpp"

namespace oka 
{
	class Camera
	{
	private:
		Vec3 m_position;
		Vec3 m_target;
		Vec3 m_up;
		glm::mat4 m_viewMatrix;
		double m_fovy;//ìxêî Ç≈ä«óù
		double m_aspect;
		double m_zNear;
		double m_zFar;

	public:
		Camera();
		~Camera() {};

		void Perspective();
		void SetViewMatrix(const Vec3 _eye,const Vec3 _target,const Vec3 _up);
		void MultViewMatrix();
		void Ortho(const float _left, const float _right, const float _bottom, const float _top, const float _near, const float _far);

		glm::mat4 GetViewMatrix()const;	
	};

}//namespace oka

extern oka::Camera *g_camera;

#endif

