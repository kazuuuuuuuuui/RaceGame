#include"camera.h"
#include"Matrix.h"
#include"glm\gtc\matrix_transform.hpp"
#include"glut.h"

oka::Camera *g_camera = nullptr;

namespace oka
{

	void Camera::update(const int _type) {

		if (TYPE_3D == _type) {

			//���e�ϊ��s��̐ݒ� 
			glMatrixMode(GL_PROJECTION);

			//�ϊ��s��̏����� 
			glLoadIdentity();

			//�������e�@�̎��̐�gluPerspactive(th, w/h, near, far);
			gluPerspective(m_angle, m_aspect, m_zNear, m_zFar);

			//�r���[�s��̐ݒ�
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			//���C�g�̈ʒu
			float v[] = { 0, 1, 1, 0 };
			glLightfv(
				GL_LIGHT0,  // GLenum light
				GL_POSITION,// GLenum pname
				v);         // const GLfloat *params

			gluLookAt(0, 10, 0, 0, 0, -5, 0, 1, 0);

			//�r���[�s��
			//viewMatrix = glm::lookAt(

			//	// ���_�̈ʒux,y,z;
			//	glm::vec3(m_position.m_x, m_position.m_y, m_position.m_z),

			//	// ���E�̒��S�ʒu�̎Q�Ɠ_���Wx,y,z
			//	glm::vec3(m_target.m_x, m_target.m_y, m_target.m_z),

			//	//���E�̏�����̃x�N�g��x,y,z
			//	glm::vec3(m_up.m_x, m_up.m_y, m_up.m_z));

			////�r���[�s��K�p
			//glMultMatrixf((GLfloat*)&viewMatrix);

		}

		else if (TYPE_2D == _type) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glOrtho(
				0, 300,  // GLdouble left, right
				0, 300,  // GLdouble bottom, top,
				1, -1); // GLdouble zNear, zFar


		}
	}

}//namespace oka
