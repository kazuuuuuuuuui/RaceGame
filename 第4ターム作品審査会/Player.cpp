#define BUTTON_A (1)
#define BUTTON_X (4)

#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>
#include"Course.h"
#include"player.h"
#include"BmpImage.h"
#include"glut.h"

Player *player = nullptr;

//-------------------------------------
//���@�̍X�V

void Player::update(){

	m_speed += m_accel;
	m_position += m_speed;

	//���������銵��
	m_speed *= 0.965f;

	//���΂��Q�b�g�������̔���Ə���
	if (getMagicStone()){


	}

	inDart();

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

		/*glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		std::vector<float>::iterator itr_v = m_vertex.begin();
		glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

		std::vector<float>::iterator itr_n = m_normal.begin();
		glNormalPointer(GL_FLOAT, 0, &(*itr_n));

		std::vector<unsigned short>::iterator itr_i = m_index.begin();

		glDrawElements(GL_TRIANGLES, m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));*/

		

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
//�v���C���[�����΂��Q�b�g�������ǂ�������
//�Q�b�g���Ă�����true �Q�b�g���Ă��Ȃ�������false��Ԃ�

bool Player::getMagicStone(){

	//�v���C���[�Ɩ��΂Ƃ̋���
	glm::vec3 distance;
	distance.x = (magicStone->m_position.x - m_position.x);
	distance.y = (magicStone->m_position.y - m_position.y);
	distance.z = (magicStone->m_position.z - m_position.z);

	float length = sqrt(distance.x*distance.x + distance.y*distance.y + distance.z*distance.z);

	if (length < 1.f){
		return true;
	}
	else{
		return false;
	}

}

//-------------------------------------
//�v���C���[���_�[�g�ɓ����Ă��邩����
//�����Ă�����true �����Ă��Ȃ�������false��Ԃ�

bool Player::inDart(){

	

	return false;
}




