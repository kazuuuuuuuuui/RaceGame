#include"MagicStone.h"
#include"glut.h"

MagicStone *magicStone = nullptr;

//���΂̃e�N�X�`�����i�[����
GLuint fire_handle = 0;

//-------------------------------------
//����(�A�C�e��)�̕`��

void MagicStone::draw(){

	glPushMatrix();
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, fire_handle);

		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(0, m_rotate.x, m_rotate.y, m_rotate.z);
		glScalef(m_scale.x, m_scale.y, m_scale.z);

		glColor3f(1, 1, 1);

		glBegin(GL_QUADS);
		{
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);
			
			glTexCoord2f(1, 0);
			glVertex3f(1, 0, 0);

			glTexCoord2f(1, 1);
			glVertex3f(1, 1, 0);

			glTexCoord2f(0, 1);
			glVertex3f(0, 1, 0);
		}
		glEnd();

		glDisable(GL_TEXTURE_2D);

	}
	glPopMatrix();

}