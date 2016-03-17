#include<string>
#include"StrokeString.h"
#include"glut.h"

namespace oka
{
	//-------------------------------------
	//文字の太さを変更する

	void SetLineWidth(const float _width)
	{
		glLineWidth(_width);
	}

	//-------------------------------------
	//文字の太さをデフォルト値に戻す

	void SetDefaultLineWidth()
	{
		glLineWidth(1.0f);
	}

	//-------------------------------------
	//ストローク文字の出力
	//文字・描画位置・文字の大きさ・色を指定して出力

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