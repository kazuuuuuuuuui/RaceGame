#include<stdlib.h>
#include"camera.h"
#include"player.h"
#include"glm\gtc\matrix_transform.hpp"
#include"glut.h"

void Camera::update(){

	//���e�ϊ��s��̐ݒ� 
	glMatrixMode(GL_PROJECTION);

	//�ϊ��s��̏����� 
	glLoadIdentity();

	//�������e�@�̎��̐�gluPerspactive(th, w/h, near, far);
	gluPerspective(m_angle, m_aspect, m_zNear, m_zFar);

	//�r���[�s��̐ݒ�
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//�J�����̍��W�X�V
	m_position.x = player->m_position.x + sin(player->m_rotate.y) * 6;
	m_position.y = 2;
	m_position.z = player->m_position.z + cos(player->m_rotate.y) * 6;

	//�J�����̒������W�̍X�V
	m_target = player->m_position;

	gluLookAt(
		// ���_�̈ʒux,y,z;
		m_position.x, m_position.y, m_position.z,

		// ���E�̒��S�ʒu�̎Q�Ɠ_���Wx,y,z
		m_target.x, m_target.y, m_target.z,

		//���E�̏�����̃x�N�g��x,y,z
		m_up.x, m_up.y, m_up.z);


	//viewMatrix = glm::lookAt(
	//	// ���_�̈ʒux,y,z
	//	glm::vec3(m_position.m_x, m_position.m_y, m_position.m_z),

	//	// ���E�̒��S�ʒu�̎Q�Ɠ_���Wx,y,z
	//	glm::vec3(m_target.m_x, m_target.m_y, m_target.m_z),
	//	
	//	//���E�̏�����̃x�N�g��x,y,z
	//	glm::vec3(m_up.m_x, m_up.m_y, m_up.m_z)
	//	);
}
