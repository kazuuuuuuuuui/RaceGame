#include"MagicStone.h"
#include"glut.h"

MagicStone *magicStone = nullptr;

//魔石のテクスチャを格納する
GLuint fire_handle = 0;

//-------------------------------------
//魔石(アイテム)の描画

void MagicStone::draw(){

	glPushMatrix();
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, fire_handle);

		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(0, m_rotate.x, m_rotate.y, m_rotate.z);
		glScalef(m_scale.x, m_scale.y, m_scale.z);

		glColor4f(1, 1, 1, 1);

		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex3f(-0.5, -0.5, 0);

			glTexCoord2f(1, 0);
			glVertex3f(0.5, -0.5, 0);

			glTexCoord2f(1, 1);
			glVertex3f(0.5, 0.5, 0);

			glTexCoord2f(0, 1);
			glVertex3f(-0.5, 0.5, 0);
		}
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glDisable(GL_BLEND);
	}
	glPopMatrix();

}