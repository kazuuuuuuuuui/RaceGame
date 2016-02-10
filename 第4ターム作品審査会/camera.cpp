#include<stdlib.h>
#include"camera.h"
#include"Matrix.h"
#include"joysticManager.h"
#include"glm\glm.hpp"
#include"glut.h"

Camera *camera = nullptr;

void Camera::update(const int _type){

	if (TYPE_3D == _type){

		//投影変換行列の設定 
		glMatrixMode(GL_PROJECTION);

		//変換行列の初期化 
		glLoadIdentity();

		//透視投影法の視体積gluPerspactive(th, w/h, near, far);
		gluPerspective(m_angle, m_aspect, m_zNear, m_zFar);

		//ビュー行列の設定
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//ライトの位置
		float v[] = { 0, 1, 1, 0 };
		glLightfv(
			GL_LIGHT0,  // GLenum light
			GL_POSITION,// GLenum pname
			v);         // const GLfloat *params

		//ビュー行列
		viewMatrix = glm::lookAt(

			// 視点の位置x,y,z;
			glm::vec3(m_position.x, m_position.y, m_position.z),

			// 視界の中心位置の参照点座標x,y,z
			glm::vec3(m_target.x, m_target.y, m_target.z),

			//視界の上方向のベクトルx,y,z
			glm::vec3(m_up.x, m_up.y, m_up.z));

		//ビュー行列適用
		glMultMatrixf((GLfloat*)&viewMatrix);

	}

	else if (TYPE_2D == _type){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glOrtho(
			0, 300,  // GLdouble left, right
			0, 300,  // GLdouble bottom, top,
			1, -1); // GLdouble zNear, zFar


	}

	//viewMatrix = glm::lookAt(
	//	// 視点の位置x,y,z
	//	glm::vec3(m_position.m_x, m_position.m_y, m_position.m_z),

	//	// 視界の中心位置の参照点座標x,y,z
	//	glm::vec3(m_target.m_x, m_target.m_y, m_target.m_z),
	//	
	//	//視界の上方向のベクトルx,y,z
	//	glm::vec3(m_up.m_x, m_up.m_y, m_up.m_z)
	//	);
}
