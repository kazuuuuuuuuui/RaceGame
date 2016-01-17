#define BUTTON_A (1)
#define BUTTON_X (4)
#define BUTTON_Y (8)
#define BUTTON_RB (16)

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>
#include"Course.h"
#include"player.h"
#include"camera.h"
#include"BmpImage.h"
#include"glut.h"

Player *player = nullptr;


//�^�C���̈ʒu������ł�����
//��芸����
extern int flame;
extern int milliSecond;
extern int second;
extern int minute;

int getMilliSecond(int _flame);
int getSecond(int _flame);
int getMinute(int _second);



//-------------------------------------
//���@�̍X�V

void Player::update(){

	//printf("%02d::%02d::%03d\n", getMinute(getSecond(m_flame)), getSecond(m_flame), getMilliSecond(m_flame));

	//�t���[���̊Ǘ�
	m_flame++;

	sprintf(m_str_lapTime[FIRST], "%02d:%02d:%03d ", m_minute[FIRST], m_second[FIRST], m_milliSecond[FIRST]);
	sprintf(m_str_lapTime[SECOND], "%02d:%02d:%03d ", m_minute[SECOND], m_second[SECOND], m_milliSecond[SECOND]);
	sprintf(m_str_lapTime[THIRD], "%02d:%02d:%03d ", m_minute[THIRD], m_second[THIRD], m_milliSecond[THIRD]);

	//�~���b
	//m_milliSecond[m_lapCount - 1] = getMilliSecond(m_flame);

	//�b
	//m_second[m_lapCount - 1] = getSecond(m_flame);

	//��
	//m_minute[m_lapCount - 1] = getMinute(m_second[m_lapCount - 1]);

	//second = second % 60;

	//�X�s�[�h�E�|�W�V�����̍X�V
	m_speed += m_accel;
	m_position += m_speed;

	//���������銵��
	m_speed *= 0.965f;


	//����̃R�[�X�̈悩��o�Ă��Ȃ����̔���
	checkCourseOut();

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

		/*m_milliSecond[m_lapCount - 1] = m_milliSecond[m_lapCount - 1];
		m_second[m_lapCount - 1] = m_second[m_lapCount - 1];
		m_minute[m_lapCount - 1] = m_minute[m_lapCount - 1];*/

		//�~���b
		m_milliSecond[m_lapCount - 1] = getMilliSecond(m_flame);

		//�b
		m_second[m_lapCount - 1] = getSecond(m_flame);

		//��
		m_minute[m_lapCount - 1] = getMinute(m_second[m_lapCount - 1]);

		m_second[m_lapCount - 1] = m_second[m_lapCount - 1] % 60;


		/*sprintf(m_str_lapTime[FIRST], "%02d:%02d:%03d ", m_minute[FIRST], m_second[FIRST], m_milliSecond[FIRST]);
		sprintf(m_str_lapTime[SECOND], "%02d:%02d:%03d ", m_minute[SECOND], m_second[SECOND], m_milliSecond[SECOND]);
		sprintf(m_str_lapTime[THIRD], "%02d:%02d:%03d ", m_minute[THIRD], m_second[THIRD], m_milliSecond[THIRD]);*/

		//�t���[���̏�����
		m_flame = 0;

		m_lapCount++;
		m_checkFlag = false;
	}

	//�S�[���������̔���
	if (checkIsGoal()){
		m_isGoal = true;
	}

}


//-------------------------------------
//���@�̕`��

void Player::draw(){
	glPushMatrix();
	{

		//float diffuse[] = { 255 / 255.f, 255 / 255.f, 255 / 255.f, 1 };
		//glMaterialfv(
		//	GL_FRONT,   // GLenum face
		//	GL_DIFFUSE, // GLenum pname
		//	diffuse);   // const GLfloat *params

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

		//glColor3f(0, 1, 0);
		//glBegin(GL_TRIANGLES);
		//{
		//	glVertex3f(0, 0, -1.5);//��
		//	glVertex3f(-0.5, 0, 1);
		//	glVertex3f(0.5, 0, 1);
		//}
		//glEnd();

	}
	glPopMatrix();


	glPushMatrix();
	{

		//float diffuse[] = { 0 / 255.f, 0 / 255.f, 0 / 255.f, 1 };
		//glMaterialfv(
		//	GL_FRONT,   // GLenum face
		//	GL_DIFFUSE, // GLenum pname
		//	diffuse);   // const GLfloat *params

		static float angle = 0.f;
		static float scal = 0.18f;

		angle -= 5.f;

		glTranslatef(m_position.x + sin(m_rotate.y)*1.1, m_position.y + 0.5, m_position.z + cos(m_rotate.y)*1.1);
		glRotatef(m_rotate.y * 180 / M_PI, 0, 1, 0);
		glRotatef(angle, 1, 0, 0);
		glScalef(scal, scal, scal);

		std::vector<float>::iterator itr_v = m_backWheel.m_vertex.begin();
		glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

		std::vector<float>::iterator itr_n = m_backWheel.m_normal.begin();
		glNormalPointer(GL_FLOAT, 0, &(*itr_n));

		std::vector<unsigned short>::iterator itr_i = m_backWheel.m_index.begin();


		/*��֕`��*/
		glDrawElements(GL_TRIANGLES, m_backWheel.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

		//float def[] = { 1, 1, 1, 1 };
		//glMaterialfv(
		//	GL_FRONT,   // GLenum face
		//	GL_DIFFUSE, // GLenum pname
		//	def);   // const GLfloat *params
	}
	glPopMatrix();
}

//-------------------------------------
//���@�̐���

void Player::control(unsigned int _pressedKey, unsigned int _downKeys, float _x, float _y, float _z){

	//�O�i(A�{�^��)
	if (_pressedKey & BUTTON_A){

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

	//�A�C�e���̎g�p
	if (_downKeys &  BUTTON_RB){



		//�������Ă���A�C�e���̌��𒲂�
		//�A�C�e�������Ă��Ȃ�������(0)�������Ȃ�
		/*if (0 != hasMagicStoneNumber()){



		}
		else{}*/

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
//���񐔂�����̎��񐔂ɂȂ������_��true��Ԃ��S�[���Ƃ���

bool Player::checkIsGoal(){

	if (LAP_MAX < m_lapCount){

		return true;

	}

	return false;

}

//-------------------------------------
//�v���C���[�������Ă���A�C�e���̌���Ԃ�

int Player::hasMagicStoneNumber(){

	return m_hasMagicStone.size();

}