
//�X�t�B�A�}�b�s���O�p��
#define MAGICSTONR_RADIUS (0.4)
#define MAGICSTONR_SLICE (30)
#define MAGICSTONR_STACK (30)
#define MAGICSTONR_REPEAT_S (3)
#define MAGICSTONR_REPEAT_T (3)

#include"MagicStone.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"glut.h"

MagicStone *magicStone = nullptr;

//���΂̃e�N�X�`�����i�[����
GLuint fire_handle = 0;//�t�@�C�A
GLuint blizzard_handle = 0;//�u���U�h

//-------------------------------------
//����(�A�C�e��)�̕`��
//�X�t�B�A�}�b�s���O�����邽�߂̏E�����֐��Ȃ̂Ō�ŗv����

void MagicStone::draw(){

	/*glPushMatrix();
	{
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(0, m_rotate.x, m_rotate.y, m_rotate.z);
		glScalef(m_scale.x, m_scale.y, m_scale.z);

		double s, t0, t1, r0, r1, th0, th1, phi;
		double p[2][3];

		for (int j = 0; j < MAGICSTONR_STACK; j++){
			t0 = (double)j / (double)MAGICSTONR_STACK;
			t1 = (double)(j + 1) / (double)MAGICSTONR_STACK;
			th0 = M_PI * t0;
			th1 = M_PI * t1;
			r0 = MAGICSTONR_RADIUS * sin(th0);
			r1 = MAGICSTONR_RADIUS * sin(th1);
			p[0][2] = MAGICSTONR_RADIUS * cos(th0);
			p[1][2] = MAGICSTONR_RADIUS * cos(th1);

			t0 = (1.0 - t0) * MAGICSTONR_REPEAT_T;
			t1 = (1.0 - t1) * MAGICSTONR_REPEAT_T;

			glEnable(GL_TEXTURE_2D);
			
			glBindTexture(GL_TEXTURE_2D, blizzard_handle);
			
			glBegin(GL_QUAD_STRIP);
			for (int i = 0; i <= MAGICSTONR_SLICE; i++){
				s = (double)i / (double)MAGICSTONR_SLICE;
				phi = 2.0 * M_PI * s;
				p[0][0] = -r0 * cos(phi);
				p[0][1] = -r0 * sin(phi);
				p[1][0] = -r1 * cos(phi);
				p[1][1] = -r1 * sin(phi);

				s *= MAGICSTONR_REPEAT_S;

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
	glPopMatrix();*/

}