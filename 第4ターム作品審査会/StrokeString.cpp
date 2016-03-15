#include<string>
#include"StrokeString.h"
#include"glut.h"

//-------------------------------------
//ストローク文字の出力
//文字・描画位置・文字の大きさ・色を指定して出力

void StrokeString::print(const char *_character, glm::vec3 _position, float _scale, glm::vec3 _color){

	glPushMatrix();
	{

		glTranslatef(_position.x, _position.y, _position.z);
		
		glScalef(_scale, _scale, _scale);

		glColor3f(_color.x, _color.y, _color.z);

	
		for (unsigned int i = 0; i < strlen(_character); i++){
			glutStrokeCharacter(GLUT_STROKE_ROMAN, _character[i]);
		}

	}
	glPopMatrix();
}