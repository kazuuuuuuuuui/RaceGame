#include<stdio.h>
#include"Course.h"

Course *testCourse = nullptr;

//-------------------------------------
//�e�R�[�X�S�̂Ƌ�̕`��

void Course::draw(){

	glEnable(GL_TEXTURE_2D);

	//��̕`��
	/*glPushMatrix();
	{
	glBindTexture(GL_TEXTURE_2D, m_handle[BACKGROUND_TEXTURE]);

	glColor3f(1, 1, 1);

	glTranslatef(0, 0, -300.f);

	glBegin(GL_QUADS);
	{
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(0.f, 0.f, 0.f);

	glTexCoord2f(1.f, 1.f);
	glVertex3f(m_width, 0.f, 0.f);

	glTexCoord2f(1.f, 0.f);
	glVertex3f(m_width, m_height, 0);

	glTexCoord2f(0.f, 0.f);
	glVertex3f(0, m_height, 0);
	}
	glEnd();


	}
	glPopMatrix();*/


	//�R�[�X�̕`��
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, m_handle[COUSE_TEXTURE]);

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

void Course::setMagicStone(){

	for (int i = 0; i < COURSE_HEIGHT; i++){
		for (int t = 0; t < COURSE_WIDTH; t++){

			if (ITEMPOSITION == m_buffer[i][t]){
				
				//��芸����
				static int num = 0;

				magicStone[num]->m_position.x = t;
				magicStone[num]->m_position.y = 0.5f;
				magicStone[num]->m_position.z = i - COURSE_HEIGHT;

				num++;

			}

		}
	}

}
