#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include"Course.h"
#include"CourseFlag.h"


Course *course = nullptr;

//�I������Ă�R�[�X
int selectedCourse = COURSE1;


//-------------------------------------
//�R�[�X���Ŗ��t���[���s������

void Course::update(){
}



//-------------------------------------
//�e�R�[�X�S�̂Ƌ�̕`��

void Course::draw(){

	glEnable(GL_TEXTURE_2D);

	//�R�[�X�̕`��
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, m_handle);

		glColor3f(1, 1, 1);

		glBegin(GL_QUADS);
		{
			glNormal3f(0, 1, 0);
			glTexCoord2f(0.f, 1.f);
			glVertex3f(0.f, 0.f, 0.f);

			glTexCoord2f(1.f, 1.f);
			glVertex3f(m_width, 0.f, 0.f);

			glTexCoord2f(1.f, 0.f);
			glVertex3f(m_width, 0, -m_height);

			glTexCoord2f(0.f, 0.f);
			glVertex3f(0, 0, -m_height);
		}
		glEnd();

	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

//-------------------------------------
//�R�[�X��ɖ��΂�z�u����
//�摜���ォ��E���Ɍ������ēǂ�ł���

void Course::setItem(){

	for (int i = 0; i < COURSE_HEIGHT; i++){
		for (int t = 0; t < COURSE_WIDTH; t++){

			if (ITEMPOSITION == m_buffer[i][t]){

				//��芸����

				item[itemNum]->transform.m_position.x = t;
				item[itemNum]->transform.m_position.y = 0.5f;
				item[itemNum]->transform.m_position.z = i - COURSE_HEIGHT;

				itemNum++;

			}

		}
	}

}

//-------------------------------------
//�I�����ꂽ�R�[�X�Ƀ`�F�b�N�|�C���g��z�u����
//�`�F�b�N�|�C���g�̍��W�͊O���e�L�X�g�t�@�C���ɕۊ�

void Course::setCheckPoint(const char *_txtName) {

	FILE *fp = fopen(_txtName, "r");
	assert(fp != nullptr);

	for (int i = 0; i < CHECK_POINT_NUMBER; i++) {

		glm::vec3 pos;
		fscanf(fp, "(%f,%f,%f)", &pos.x, &pos.y, &pos.z);
		fscanf(fp, "%*c"); //���s�����ǂݔ�΂�

		m_checkPoint[i].m_position = pos;

	}

}

//-------------------------------------
//�I�����ꂽ�R�[�X��AI����p�̃|�C���g��z�u����
//�`�F�b�N�|�C���g�̍��W�͊O���e�L�X�g�t�@�C���ɕۊ�

void Course::setAIPoint(const char *_txtName) {

	FILE *fp = fopen(_txtName, "r");
	assert(fp != nullptr);

	for (int i = 0; i < AI_POINT_NUMBER; i++) {

		glm::vec3 pos;
		fscanf(fp, "(%f,%f,%f)", &pos.x, &pos.y, &pos.z);
		fscanf(fp, "%*c"); //���s�����ǂݔ�΂�

		m_AIPoint[i].m_position = pos;

	}

}




//-------------------------------------
//�I�΂ꂽ�R�[�X�̐���
//�`�F�b�N�|�C���g�EAI����p�̃|�C���g�E�o�b�t�@����
//�g�p����e�N�X�`���̓ǂݍ��݂��s��

Course* createCourse(){

	Course *newCourse = new Course();

	if (COURSE1 == selectedCourse){

		//�`�F�b�N�|�C���g�̈ʒu�ݒ�
		newCourse->setCheckPoint("txt/course1_cp.txt");
		
		//AI�|�C���g�̈ʒu�ݒ�
		newCourse->setAIPoint("txt/course1_AIp.txt");

		//�g�p����e�N�X�`���̓ǂݍ���
		newCourse->m_handle = BmpImage::loadImage("bmp/course1/course1.bmp");

		//�o�b�t�@�̍쐬
		BmpImage::makeBuffer("bmp/course1/buffer1.bmp", newCourse->m_buffer);
	}
	

	//�R�[�X2(��)
	else if (COURSE2 == selectedCourse){

		//�`�F�b�N�|�C���g�̈ʒu�ݒ�
		newCourse->setCheckPoint("txt/course2_cp.txt");

		//AI�|�C���g�̈ʒu�ݒ�
		newCourse->setAIPoint("txt/course2_AIp.txt");

		//�g�p����e�N�X�`���̓ǂݍ���
		newCourse->m_handle = BmpImage::loadImage("bmp/course2/course2.bmp");
		
		//�o�b�t�@�̍쐬
		BmpImage::makeBuffer("bmp/course2/buffer2.bmp", newCourse->m_buffer);

	}

	newCourse->setItem();

	return newCourse;

}
