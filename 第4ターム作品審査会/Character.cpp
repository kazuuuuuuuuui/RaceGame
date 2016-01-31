#include"Character.h"
#include<stdio.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"GameManager.h"
#include"Course.h"
#include"Character.h"
#include"Item.h"
#include"camera.h"
#include"BmpImage.h"
#include"Material.h"
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtx\transform.hpp"
#include"glut.h"


//�^�C���̈ʒu������ł�����
//��芸����
extern int flame;
extern int milliSecond;
extern int second;
extern int minute;
extern bool startRace;

int getMilliSecond(int _flame);
int getSecond(int _flame);
int getMinute(int _second);

//-------------------------------------
//�L�����N�^�[���ׂĂ��Ǘ�����x�N�^�[
std::vector<Character*> character;

//-------------------------------------
//���@�̍X�V
//�S�[���������_�ōX�V���~�߂�

void Character::update(){

	if (false == m_isGoal){

		//�t���[���̊Ǘ�
		m_flame++;

		//�_�b�V���Q�[�W�̉�
		m_dashPower += 0.1f;

		if (m_dashPower >= DASH_GAUGE_MAX){

			m_dashPower = DASH_GAUGE_MAX;

		}


		//1���������̔���
		if (countLap()){

			//�~���b
			m_milliSecond[m_lapCount - 1] = getMilliSecond(m_flame);

			//�b
			m_second[m_lapCount - 1] = getSecond(m_flame);

			//��
			m_minute[m_lapCount - 1] = getMinute(m_second[m_lapCount - 1]);

			m_second[m_lapCount - 1] = m_second[m_lapCount - 1] % 60;

			//�t���[���̏�����
			m_flame = 0;

			//�`�F�b�N�|�C���g�̏�����
			for (int i = 0; i < CHECK_POINT_NUMBER; i++){
				m_passCheckPoint[i] = false;
			}

			//AI�|�C���g�̏�����
			for (int i = 0; i < AI_POINT_NUMBER; i++){
				m_passAIPoint[i] = false;
			}

			m_nowPoint = 0;

			m_lapCount++;


		}

	}

	sprintf_s(m_str_lapTime[FIRST], "%02d:%02d:%03d ", m_minute[FIRST], m_second[FIRST], m_milliSecond[FIRST]);
	sprintf_s(m_str_lapTime[SECOND], "%02d:%02d:%03d ", m_minute[SECOND], m_second[SECOND], m_milliSecond[SECOND]);
	sprintf_s(m_str_lapTime[THIRD], "%02d:%02d:%03d ", m_minute[THIRD], m_second[THIRD], m_milliSecond[THIRD]);

	//1�t���[���O�̃|�W�V�����X�V
	m_lastPosition = m_position;

	//�X�s�[�h�E�|�W�V�����̍X�V
	m_speed += (m_dashSpeed + m_accel);

	m_position += m_speed;

	//�O�ւƌ�ւ̃|�W�V�����X�V

	//�O�֍��W
	m_frontPosition.x = m_position.x - sin(m_rotate.y)*1.55f;
	m_frontPosition.y = 0.5f;
	m_frontPosition.z = m_position.z - cos(m_rotate.y)*1.55f;

	//��֍��W
	m_backPosition.x = m_position.x + sin(m_rotate.y)*1.15f;
	m_backPosition.y = 0.5f;
	m_backPosition.z = m_position.z + cos(m_rotate.y)*1.15f;


	//���̍X�V
	m_smoke.update();
	m_smoke.m_basePosition.x = m_position.x + sin(m_rotate.y)*1.7f;
	m_smoke.m_basePosition.y = 0.5f;
	m_smoke.m_basePosition.z = m_position.z + cos(m_rotate.y)*1.7f;

	//�_�b�V���G�t�F�N�g�̍X�V
	if (nullptr != m_dash){
		m_dash->m_basePosition.x = m_position.x + sin(m_rotate.y)*0.8;
		m_dash->m_basePosition.y = -0.2f;
		m_dash->m_basePosition.z = m_position.z + cos(m_rotate.y)*0.8;
	}

	//���������銵��
	m_speed *= 0.965f;

	//�_�b�V���̌�������
	m_dashSpeed *= 0.96;

	if (m_dash != NULL){

		if (glm::length(m_dashSpeed) <= 0.0001){
			//�_�b�V����ԉ���
			m_isDash = false;
			m_dash->m_isActive = false;
		}

	}

	//printf("%f\n", glm::length(m_dashSpeed));


	//�ԗւ̉�]�X�s�[�h�X�V
	//*100�͕␳�l
	m_wheelSpeed = glm::length(m_speed) * 100;


	//�X���b�v����
	slip();

	//�`�F�b�N�|�C���g��ʉ߂��Ă��邩�̔��菈��
	for (int i = 0; i < CHECK_POINT_NUMBER; i++){

		if (false == m_passCheckPoint[i] && course->m_checkPoint[i].checkPassFlag(m_position)){


			m_passCheckPoint[i] = true;
			m_nowPoint++;


		}

	}

	//�G��AI�̋�������
	for (int i = 0; i < AI_POINT_NUMBER; i++){

		if (false == m_passAIPoint[i] && course->m_AIPoint[i].checkPassFlag(m_position)){

			m_passAIPoint[i] = true;

			m_nextPoint++;

			if (AI_POINT_NUMBER == m_nextPoint){
				m_nextPoint = 0;
			}

		}

	}

	//�ڎw���Ă���`�F�b�N�|�C���g�ւ̋����̍X�V
	m_nextCheckPointLength = checkNextCheckPointLength();

	//����̃R�[�X�̈悩��o�Ă��Ȃ����̔���
	checkCourseOut();

	//�_�[�g�ɓ��������̔���Ə���
	if (inDart()){
		m_speed *= 0.9f;
	}

	//�S�[���������̔���
	if (checkIsGoal()){
		m_isGoal = true;
	}

}

//-------------------------------------
//���@�̕`��

void Character::draw(){

	/*�ԑ̕`��*/
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{

		glEnable(GL_LIGHTING);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glPushMatrix();
		{

			//�s��v�Z
			glm::mat4 translate = glm::translate(glm::vec3(m_position.x, m_position.y, m_position.z));

			glm::mat4 rotate = glm::rotate(m_rotate.y + m_crashRotate, glm::vec3(0, 1, 0))*
				glm::rotate(m_rotate.z, glm::vec3(0, 0, 1));


			glm::mat4 scale = glm::scale(glm::vec3(m_scale.x, m_scale.y, m_scale.z));

			//�e�̍s��
			m_matrix = translate *rotate *scale;

			//�s��K��
			glMultMatrixf((GLfloat*)&m_matrix);

			std::vector<float>::iterator itr_v = m_body.m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

			std::vector<float>::iterator itr_n = m_body.m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*itr_n));

			std::vector<unsigned short>::iterator itr_i = m_body.m_index.begin();


			//�}�e���A���̐ݒ�

			/*	switch (m_type){

				case PLAYER1:

				float diffuse[4] = { 1, 0, 0, 1 };
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

				break;

				case PLAYER2:

				float diffuse[4] = { 0, 1, 0, 1 };
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

				break;

				case PLAYER3:

				float diffuse[4] = { 0, 0, 1, 1 };
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

				break;

				case PLAYER4:

				float diffuse[4] = { 0, 1, 1, 1 };
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

				break;
				}*/

			/*float specular[] = { 1, 0, 0, 1 };
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialf(GL_FRONT, GL_SHININESS, 100);*/

			glDrawElements(GL_TRIANGLES, m_body.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

		}
		glPopMatrix();


		//��]����
		static float angle = 0;

		//���
		glPushMatrix();
		{
			angle -= m_wheelSpeed;
			angle *= 0.98f;

			//angle�̒l��-10000�`0�ň�������
			if (angle < -200.f){
				angle = 0.f;
			}

			glm::mat4 childRotate = glm::rotate(angle, glm::vec3(1, 0, 0));

			glm::mat4 childScale = glm::scale(glm::vec3(0.9f, 0.9f, 0.9f));

			//�q���̍s��
			glm::mat4 child = childRotate * childScale;

			//�I�t�Z�b�g
			glm::mat4 offSet = glm::translate(glm::vec3(0.0f, 3.1f, 6.3f));

			glm::mat4 myMatrix = m_matrix * offSet *child;


			glMultMatrixf((GLfloat*)&myMatrix);


			std::vector<float>::iterator itr_v = m_backWheel.m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

			std::vector<float>::iterator itr_n = m_backWheel.m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*itr_n));

			std::vector<unsigned short>::iterator itr_i = m_backWheel.m_index.begin();

			float diffuse[] = { 0, 0, 0, 1 };
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

			/*��֕`��*/
			glDrawElements(GL_TRIANGLES, m_backWheel.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

		}
		glPopMatrix();


		//�O��
		glPushMatrix();
		{

			glm::mat4 childRotate = glm::rotate(angle, glm::vec3(1, 0, 0));

			glm::mat4 childScale = glm::scale(glm::vec3(0.72f, 0.72f, 0.72f));

			//�q���̍s��
			glm::mat4 child = childRotate * childScale;

			//�I�t�Z�b�g
			glm::mat4 offSet = glm::translate(glm::vec3(0.0f, 2.8f, -9.f));

			glm::mat4 myMatrix = m_matrix * offSet *child;

			glMultMatrixf((GLfloat*)&myMatrix);

			std::vector<float>::iterator itr_v = m_backWheel.m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

			std::vector<float>::iterator itr_n = m_backWheel.m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*itr_n));

			std::vector<unsigned short>::iterator itr_i = m_backWheel.m_index.begin();

			glDrawElements(GL_TRIANGLES, m_backWheel.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

		}
		glPopMatrix();

	}
	glPopAttrib();

	//�e���`��
	//�ԑ�

	glColor3f(100 / 255.f, 100 / 255.f, 100 / 255.f);

	glPushMatrix();
	{

		//�s��v�Z
		glm::mat4 parentTranslate = glm::translate(glm::vec3(m_position.x, 0.01f, m_position.z));

		glm::mat4 parentRotate = glm::rotate(m_rotate.y + m_crashRotate, glm::vec3(0, 1, 0));

		glm::mat4 parentScale = glm::scale(glm::vec3(m_scale.x, 0, m_scale.z));

		//�e�̍s��
		m_matrix = parentTranslate *parentRotate * parentScale;

		//�s��K��
		glMultMatrixf((GLfloat*)&m_matrix);

		std::vector<float>::iterator itr_v = m_body.m_vertex.begin();
		glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

		std::vector<unsigned short>::iterator itr_i = m_body.m_index.begin();

		glDrawElements(GL_TRIANGLES, m_body.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

	}
	glPopMatrix();


	//�e���`��
	//���

	glPushMatrix();
	{

		//�q���̍s��
		glm::mat4 child = glm::scale(glm::vec3(0.92f, 0, 0.92f));

		//�I�t�Z�b�g
		glm::mat4 offSet = glm::translate(glm::vec3(0.0f, 0.01f, 6.3f));

		glm::mat4 myMatrix = m_matrix * offSet *child;


		glMultMatrixf((GLfloat*)&myMatrix);




		std::vector<float>::iterator itr_v = m_backWheel.m_vertex.begin();
		glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

		std::vector<unsigned short>::iterator itr_i = m_backWheel.m_index.begin();


		/*��֕`��*/
		glDrawElements(GL_TRIANGLES, m_backWheel.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

	}
	glPopMatrix();

	//debug
	//�{��
	glColor3f(1, 1, 1);
	glPushMatrix();
	{
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(m_rotate.y * 180 / M_PI, 0, 1, 0);
		glScalef(m_scale.x, m_scale.y, m_scale.z);
		glutSolidCube(1);
	}
	glPopMatrix();
	//�O
	glPushMatrix();
	{
		glTranslatef(m_frontPosition.x, m_frontPosition.y - 0.5f, m_frontPosition.z);
		glRotatef(m_rotate.y * 180 / M_PI, 0, 1, 0);
		glScalef(m_scale.x, m_scale.y, m_scale.z);
		glutSolidCube(1);
	}
	glPopMatrix();
	//���
	glPushMatrix();
	{
		glTranslatef(m_backPosition.x, m_backPosition.y - 0.5f, m_backPosition.z);
		glRotatef(m_rotate.y * 180 / M_PI, 0, 1, 0);
		glScalef(m_scale.x, m_scale.y, m_scale.z);
		glutSolidCube(1);
	}
	glPopMatrix();


}


//-------------------------------------
//�������Ă���A�C�e���̕`��

void Character::drawHasItem(){

	for (unsigned int i = 0; i < m_hasItem.size(); i++){


		//�e�N�X�`���̐ݒ�
		switch (m_hasItem[i]){
		case FIRE:

			glBindTexture(GL_TEXTURE_2D, ItemFire);

			break;

		case BLIZZARD:

			glBindTexture(GL_TEXTURE_2D, ItemBlizzard);

			break;

		}


		glPushMatrix();
		{
			glTranslatef(m_position.x + sin(m_rotate.y) * 2.8 + sin(m_rotate.y)*i,
				0.5f,
				m_position.z + cos(m_rotate.y) * 2.8 + cos(m_rotate.y)*i);

			glColor3f(1, 1, 1);

			double s, t0, t1, r0, r1, th0, th1, phi;
			double p[2][3];

			for (int j = 0; j < ITEM_STACK; j++){
				t0 = (double)j / (double)ITEM_STACK;
				t1 = (double)(j + 1) / (double)ITEM_STACK;
				th0 = M_PI * t0;
				th1 = M_PI * t1;
				r0 = ITEM_RADIUS * sin(th0);
				r1 = ITEM_RADIUS * sin(th1);
				p[0][2] = ITEM_RADIUS * cos(th0);
				p[1][2] = ITEM_RADIUS * cos(th1);

				t0 = (1.0 - t0) * ITEM_REPEAT_T;
				t1 = (1.0 - t1) * ITEM_REPEAT_T;

				glEnable(GL_TEXTURE_2D);

				glBegin(GL_QUAD_STRIP);
				for (int i = 0; i <= ITEM_SLICE; i++){
					s = (double)i / (double)ITEM_SLICE;
					phi = 2.0 * M_PI * s;
					p[0][0] = -r0 * cos(phi);
					p[0][1] = -r0 * sin(phi);
					p[1][0] = -r1 * cos(phi);
					p[1][1] = -r1 * sin(phi);

					s *= ITEM_REPEAT_S;

					glTexCoord2d(s, t0);
					glNormal3dv(p[0]);
					glVertex3dv(p[0]);

					glTexCoord2d(s, t1);
					glNormal3dv(p[1]);
					glVertex3dv(p[1]);
				}
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

		}
		glPopMatrix();

	}

}


//-------------------------------------
//����̃R�[�X�̈悩��o�Ă��Ȃ����̔��f��
//�o�Ă����ꍇ�̉����߂�����

void Character::checkCourseOut(){

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
//�ڎw���Ă���`�F�b�N�|�C���g�܂ł̋�����Ԃ�

float Character::checkNextCheckPointLength(){

	glm::vec3 v;

	v = m_position - course->m_checkPoint[m_nowPoint].m_position;

	return glm::length(v);
}

//-------------------------------------
//�v���C���[���_�[�g�ɓ����Ă��邩����
//�����Ă�����true �����Ă��Ȃ�������false��Ԃ�

bool Character::inDart(){

	//�v���C���[���ǂ̃s�N�Z����ɂ��邩���f��
	//�����̃s�N�Z�����ɂ���Ĕ��肷��

	if (course->m_buffer[COURSE_HEIGHT - 1 + (int)m_position.z][(int)m_position.x] == DART){

		return true;

	}
	else{

		return false;

	}
}

//-------------------------------------
//�A�C�e���ɓ����������̃X���b�v����

void Character::slip(){

	if (m_isHitItem){

		m_speed = { 0.f, 0.f, 0.f };

	}

	m_crashRotate *= 0.9f;

	if (m_crashRotate < 0.5f){

		m_isHitItem = false;

	}


}



//-------------------------------------
//�v���C���[���R�[�X����������1���������ǂ����̔�����s��
//�S�[���̈ʒu�ɂ���Ƃ��Ƀ`�F�b�N�|�C���g��ʉ߂��Ă��邩���ʂ���
//�t���O��true�̏�Ԃ̂Ƃ��̂�true��Ԃ�1���ƃJ�E���g����

bool Character::countLap(){

	if (course->m_buffer[COURSE_HEIGHT - 1 + (int)m_position.z][(int)m_position.x] == GOAL){

		bool fg = true;

		for (int i = 0; i < CHECK_POINT_NUMBER; i++){

			fg &= m_passCheckPoint[i];

		}

		if (fg == true){

			return true;

		}


	}

	return false;

}

//-------------------------------------
//�v���C���[���S�[���������̔���
//���񐔂�����̎��񐔂ɂȂ������_��true��Ԃ��S�[���Ƃ���

bool Character::checkIsGoal(){

	if (LAP_MAX < m_lapCount){

		return true;

	}

	return false;

}

//-------------------------------------
//�v���C���[�������Ă���A�C�e���̌���Ԃ�

int Character::hasItemNumber(){

	return m_hasItem.size();

}

//-------------------------------------
//�v���C���[���A�C�e���������Ă���Ƃ��̂�
//�����Ă���A�C�e���̃��X�g�̎�ނ�Ԃ�

int Character::hasItemLast(){

	int itemLast = m_hasItem.size() - 1;

	return m_hasItem[itemLast];

}