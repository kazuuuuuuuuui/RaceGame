#define BUTTON_A (1)
#define BUTTON_X (4)

#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>
#include"Course.h"
#include"player.h"
#include"glut.h"

Player *player = nullptr;

//-------------------------------------
//���@�̍X�V

void Player::update(){

	m_speed += m_accel;
	m_position += m_speed;

	//���������銵��
	m_speed *= 0.965f;

}


//-------------------------------------
//���@�̕`��

void Player::draw(){
	glPushMatrix();
	{
		/*���@����*/
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(m_rotate.y * 180 / M_PI, 0, 1, 0);
		glScalef(m_scale.x, m_scale.y, m_scale.z);

		glColor3f(0, 1, 0);
		glBegin(GL_TRIANGLES);
		{
			glVertex3f(0, 0, -1.5);
			glVertex3f(-0.5, 0, 1);
			glVertex3f(0.5, 0, 1);
		}
		glEnd();

	}
	glPopMatrix();
}

//-------------------------------------
//���@�̐���

void Player::control(unsigned int _key, float _x, float _y, float _z){

	//�O�i(A�{�^��)
	if (_key & BUTTON_A){

		//�����x�̐ݒ�
		//-0.005f�͕␳�l
		glm::vec3 accelIncrement(-0.01*sin(m_rotate.y), 0, -0.01*cos(m_rotate.y));
		m_accel = accelIncrement;
	}
	else{
		m_accel = { 0.f, 0.f, 0.f };
	}

	//���(x�{�^��)
	/*if (_key & BUTTON_X){
		m_speed.z = 0.1f;
		}*/

	//���ʉE�Ɉړ�
	if ((_key & BUTTON_A || _key & BUTTON_X) && _x > 0.9){
		m_rotate.y -= 0.02f;
	}

	//���ʍ��Ɉړ�
	//0.05f�͕␳�l
	if ((_key & BUTTON_A || _key & BUTTON_X) && _x < -0.9){
		m_rotate.y += 0.02f;
	}

}

//-------------------------------------
//�v���C���[���_�[�g�ɓ����Ă��邩����
//�����Ă�����true �����Ă��Ȃ�������false��Ԃ�

bool Player::inDart(){
	/*if (testCourse->){
		return true;
	}
	else{
		return false;
	}*/
	return false;
}



