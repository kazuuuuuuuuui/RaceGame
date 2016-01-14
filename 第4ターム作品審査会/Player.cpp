#define BUTTON_A (1)
#define BUTTON_X (4)
#define BUTTON_Y (8)

#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>
#include"Course.h"
#include"player.h"
#include"camera.h"
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


	//����̃R�[�X�̈悩��o�Ă��Ȃ����̔���
	checkCourseOut();

	//���΂��Q�b�g�������̔���Ə���
	if (getMagicStone()){}

	//�_�[�g�ɓ��������̔���Ə���
	if (inDart()){
		m_speed *= 0.9f;
	}

	//�`�F�b�N�|�C���g�������Œʉ߂������̔���
	if (passCheckPoint()){
		m_checkFlag = true;
	}

	//1���������̔���
	if (countLap()){
		m_lapCount++;
		m_checkFlag = false;
	}

	//�S�[���������̔���
	if (isGoal()){
		/*

		�S�[���������̏����L�q

		*/
	}

}


//-------------------------------------
//���@�̕`��

void Player::draw(){
	glPushMatrix();
	{

		float diffuse[] = { 77 / 255.f, 77 / 255.f, 77 / 255.f, 1 };
		glMaterialfv(
			GL_FRONT,   // GLenum face
			GL_DIFFUSE, // GLenum pname
			diffuse);   // const GLfloat *params

		glTranslatef(m_position.x, m_position.y, m_position.z);

		glRotatef(m_rotate.y * 180 / M_PI, 0, 1, 0);
		glRotatef(180, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);

		//glScalef(m_scale.x, m_scale.y, m_scale.z);
		glScalef(0.18, 0.18, 0.18);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		std::vector<float>::iterator itr_v = m_boby.m_vertex.begin();
		glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

		std::vector<float>::iterator itr_n = m_boby.m_normal.begin();
		glNormalPointer(GL_FLOAT, 0, &(*itr_n));

		std::vector<unsigned short>::iterator itr_i = m_boby.m_index.begin();
		
		
		/*�ԑ̕`��*/
		glDrawElements(GL_TRIANGLES, m_boby.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

		float def[] = { 1, 1, 1, 1 };
		glMaterialfv(
			GL_FRONT,   // GLenum face
			GL_DIFFUSE, // GLenum pname
			def);   // const GLfloat *params





		//	glColor3f(0, 1, 0);
		//	glBegin(GL_TRIANGLES);
		//	{
		//		glVertex3f(0, 0, -1.5);//��
		//		glVertex3f(-0.5, 0, 1);
		//		glVertex3f(0.5, 0, 1);
		//	}
		//	glEnd();

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
		glm::vec3 accelIncrement(-0.015*sin(m_rotate.y), 0, -0.015*cos(m_rotate.y));
		m_accel = accelIncrement;
	}
	else{
		m_accel = { 0.f, 0.f, 0.f };
	}

	//���ʉE�Ɉړ�
	if (_x > 0.9){
		m_rotate.y -= 0.02f;

	}

	//���ʍ��Ɉړ�
	if (_x < -0.9){
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
//����̃R�[�X�̈悩��o�Ă��Ȃ����̔��f��
//�o�Ă����ꍇ�̉����߂�����

void Player::checkCourseOut(){

	if (m_position.x < 0.f){
		m_position.x = 0.f;
	}

	if (m_position.x > COURSE_WIDTH){
		m_position.x = COURSE_WIDTH;
	}

	if (m_position.z > 0){
		m_position.z = 0.f;
	}

	//256�̂܂܂���256�Ԗڂ̃s�N�Z�����ɃA�N�Z�X���Ă��܂��̂ŕ␳�l+1���Ă���
	if (m_position.z < -COURSE_HEIGHT + 1){
		m_position.z = -COURSE_HEIGHT + 1;
	}

}

//-------------------------------------
//�v���C���[���_�[�g�ɓ����Ă��邩����
//�����Ă�����true �����Ă��Ȃ�������false��Ԃ�

bool Player::inDart(){

	//�v���C���[���ǂ̃s�N�Z����ɂ��邩���f��
	//�����̃s�N�Z�����ɂ���Ĕ��肷��

	if (testCourse->m_buffer[COURSE_HEIGHT - 1 + (int)m_position.z][(int)m_position.x] == DART){

		return true;

	}
	else{

		return false;

	}
}

//-------------------------------------
//�v���C���[���������ă`�F�b�N�|�C���g��
//�ʉ߂������ǂ����̔�����s��
//�`�F�b�N�|�C���g�̎�O�Ɉʒu���Ă�����num��1
//�`�F�b�N�|�C���g�̒���Ɉʒu���Ă�����num��2
//����ȊO��0�������Anum�̒l��1��2�ɕω������Ƃ��̂�true��Ԃ�

bool Player::passCheckPoint(){

	//�`�F�b�N�|�C���g����������
	//�ʉ߂������ǂ����𔻒肷�邽�߂̎g���̂�static�ϐ�
	static int num = 0;

	if (testCourse->m_buffer[COURSE_HEIGHT - 1 + (int)m_position.z][(int)m_position.x] == CHECK_FLONT){

		num = 1;

	}

	else if (testCourse->m_buffer[COURSE_HEIGHT - 1 + (int)m_position.z][(int)m_position.x] == CHECK_BEHIND){
		if (1 == num){
			num = 2;
			return true;
		}
		else{
			num = 2;
		}
	}

	else{
		num = 0;
	}

	return false;
}

//-------------------------------------
//�v���C���[���R�[�X����������1���������ǂ����̔�����s��
//�S�[���̈ʒu�ɂ���Ƃ��Ƀ`�F�b�N�|�C���g��ʉ߂��Ă��邩���ʂ���
//�t���O��true�̏�Ԃ̂Ƃ��̂�true��Ԃ�1���ƃJ�E���g����

bool Player::countLap(){

	if (testCourse->m_buffer[COURSE_HEIGHT - 1 + (int)m_position.z][(int)m_position.x] == GOAL && m_checkFlag == true){

		return true;

	}

	return false;

}

//-------------------------------------
//�v���C���[���S�[���������̔���
//���񐔂�3�ɂȂ������_��true��Ԃ��S�[���Ƃ���

bool Player::isGoal(){

	if (LAP_MAX == m_lapCount){

		return true;

	}

	return false;

}