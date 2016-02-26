#include"Particle.h"
#include"Fire.h"
#include"Matrix.h"
#include"glm\glm.hpp"
#include"glut.h"

//-------------------------------------
//�G�t�F�N�g�����p�[�e�B�N��1���̕`��
//�F���w�肵�ĕ`�悷��

void Particle::draw(int _type,glm::vec3 _color,GLuint _texture){

	glPushMatrix();
	{
		BillboardMatrix = glm::inverse(viewMatrix);
		BillboardMatrix[3][0] = 0;
		BillboardMatrix[3][1] = 0;
		BillboardMatrix[3][2] = 0;

		//�u�����h
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, _texture);

		glTranslatef(transform.m_position.x, transform.m_position.y, transform.m_position.z);
		
		//�r���{�[�h��]�s��K�p
		glMultMatrixf((GLfloat*)&BillboardMatrix);
		
		glScalef(transform.m_scale.x, transform.m_scale.y, transform.m_scale.z);
		
		if (_type == 0){

			glBegin(GL_QUADS);
			{
				glColor4f(_color.x, _color.y, _color.z, m_alpha);

				glTexCoord2f(0.f, 1.f);
				glVertex2f(-1.f, -1.f);
				
				glTexCoord2f(0.f, 0.f);
				glVertex2f(-1.f, 1.f);
				
				glTexCoord2f(1.f, 0.f);
				glVertex2f(1.f, 1.f);
				
				glTexCoord2f(1.f, 1.f);
				glVertex2f(1.f, -1.f);
			}
			glEnd();

		}

		else if (_type == 1){

			glBegin(GL_QUADS);
			{
				glColor4f(_color.x, _color.y, _color.z, m_alpha);

				glTexCoord2f(0.f, 1.f);
				glVertex2f(0.f, 0.f);

				glTexCoord2f(0.f, 0.f);
				glVertex2f(0.f, 1.f);

				glTexCoord2f(1.f, 0.f);
				glVertex2f(1.f, 1.f);

				glTexCoord2f(1.f, 1.f);
				glVertex2f(1.f, 0.f);
			}
			glEnd();

		}

	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}