#include"Course.h"

Course *testCourse = nullptr;

//-------------------------------------
//各コースの描画

void Course::draw(){
	glPushMatrix();
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_handle);

		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.f, 0.f);
			glVertex3f(0.f, 0.f, 0.f);

			glTexCoord2f(1.f, 0.f);
			glVertex3f(m_width, 0.f, 0.f);

			glTexCoord2f(1.f, 1.f);
			glVertex3f(m_width, 0, -m_height);

			glTexCoord2f(0.f, 1.f);
			glVertex3f(0, 0, -m_height);
		}
		glEnd();

		glDisable(GL_TEXTURE_2D);

	}
	glPopMatrix();
}
