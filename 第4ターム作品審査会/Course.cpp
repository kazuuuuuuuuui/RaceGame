#include"Course.h"

Course *testCourse = nullptr;

//-------------------------------------
//各コース全体と空の描画

void Course::draw(){

	glEnable(GL_TEXTURE_2D);

	//空の描画
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


	//コースの描画
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
