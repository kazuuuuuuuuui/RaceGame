#include<string>
#include"StrokeString.h"
#include"glm\glm.hpp"
#include"Vec3.h"
#include"glut.h"

namespace oka
{
	//-------------------------------------
	//�����̑�����ύX����

	void SetLineWidth(const float _width)
	{
		glLineWidth(_width);
	}

	//-------------------------------------
	//�����̑������f�t�H���g�l�ɖ߂�

	void SetDefaultLineWidth()
	{
		glLineWidth(1.0f);
	}

	//-------------------------------------
	//�X�g���[�N�����̏o��
	//�����E�`��ʒu�E�����̑傫���E�F�E�������w�肵�ďo��

	void DrawString(const char *_str, const glm::vec2 _position, const float _scale, const Vec3 _color,const float _width)
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			glColor3f(_color.m_x, _color.m_y, _color.m_z);

			glLineWidth(_width);

			glPushMatrix();
			{
				glTranslatef(_position.x, _position.y, 1.0f);
				glScalef(_scale, _scale, _scale);

				for (unsigned int i = 0; i < strlen(_str); i++)
				{
					glutStrokeCharacter(GLUT_STROKE_ROMAN, _str[i]);
				}
			}
			glPopMatrix();
		}
		glPopAttrib();
	}

}//namespace oka