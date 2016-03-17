#include<string>
#include"StrokeString.h"
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
	//�����E�`��ʒu�E�����̑傫���E�F���w�肵�ďo��

	void DrawString(const char *_str, const float _x, const float _y, const float _scale)
	{
		glPushMatrix();
		{
			glTranslatef(_x, _y, 1.0f);
			glScalef(_scale, _scale, _scale);

			for (unsigned int i = 0; i < strlen(_str); i++)
			{
				glutStrokeCharacter(GLUT_STROKE_ROMAN, _str[i]);
			}
		}
		glPopMatrix();
	}

}//namespace oka