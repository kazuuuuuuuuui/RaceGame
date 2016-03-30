#include"Camera.h"
#include"Mat4�~4.h"
#include"glut.h"

#include"Character.h"

oka::Camera *g_camera = nullptr;//�N���X�̃C���X�^���X�ɂ���H

namespace oka
{

	//-------------------------------------
	//�f�t�H���g�R���X�g���N�^

	Camera::Camera():
		m_fovy(60.0),m_aspect(1.0),m_zNear(0.1),m_zFar(1000.0),
		m_position(0.0f, 0.0f, 0.0f),m_target(0.0f, 0.0f, 0.0f),m_up(0.0f, 1.0f, 0.0f)
	{}


	//-------------------------------------
	//�����ˉe�s��̓K��

	void Camera::Perspective()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		float fov = m_fovy*M_PI / 180;

		Mat4x4 perspective = Mat4x4::Perspective(fov, m_aspect, m_zNear, m_zFar);

		glMultMatrixf((GLfloat*)&perspective);
	}

	//-------------------------------------
	//�r���[�s��̐ݒ�

	void Camera::SetViewMatrix(const Vec3 _position, const Vec3 _target, const Vec3 _up)
	{
		m_position = _position;
		m_target = _target;
		m_up = _up;

		m_viewMatrix = glm::lookAt(
			glm::vec3(m_position.m_x, m_position.m_y, m_position.m_z),
			glm::vec3(m_target.m_x, m_target.m_y, m_target.m_z),
			glm::vec3(m_up.m_x, m_up.m_y, m_up.m_z));
	}


	//-------------------------------------
	//�r���[�s��̎擾

	glm::mat4 Camera::GetViewMatrix()const
	{
		return m_viewMatrix;
	}


	//-------------------------------------
	//�r���[�s��̓K��
	
	void Camera::MultViewMatrix()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//��ňړ�
		//���C�g�̈ʒu
		float v[] = { 0, 1, 1, 0 };
		glLightfv(
			GL_LIGHT0,  // GLenum light
			GL_POSITION,// GLenum pname
			v);         // const GLfloat *params

		glMultMatrixf((GLfloat*)&m_viewMatrix);
	}

	//-------------------------------------
	//���ˉe�s��̐ݒ�ƓK��

	void Camera::Ortho(const float _left, const float _right, const float _bottom, const float _top, const float _near, const float _far)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		Mat4x4 mat = Mat4x4::Ortho(_left, _right, _bottom, _top, _near, _far);

		glMultMatrixf((GLfloat*)&mat);
	}

}//namespace oka
