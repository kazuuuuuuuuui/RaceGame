#define _USE_MATH_DEFINES
#include<math.h>
#include"CourseFlag.h"

//debug
void Circle2D(float radius, int x, int y)
{
	for (float th1 = 0.0; th1 <= 360.0; th1 = th1 + 1.0)
	{
		float th2 = th1 + 10.0;
		float th1_rad = th1 / 180.0 * M_PI;
		float th2_rad = th2 / 180.0 * M_PI;

		float x1 = radius * cos(th1_rad);
		float y1 = radius * sin(th1_rad);
		float x2 = radius * cos(th2_rad);
		float y2 = radius * sin(th2_rad);

		glBegin(GL_LINES);
		glVertex2f(x1 + x, y1 + y);
		glVertex2f(x2 + x, y2 + y);
		glEnd();
	}
}



void CourseFlag::draw(){
	glPushMatrix();
	{
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(90, 1, 0, 0);
		Circle2D(15, 0, 0);
		glutSolidCube(0.5);
	}
	glPopMatrix();
}


//周回判定をとるためのコースフラグを通っているか判定する


bool CourseFlag::checkPassFlag(glm::vec3 _position){

	glm::vec3 distance;

	distance.x = (m_position.x - _position.x);
	distance.y=0;
	distance.z = (m_position.z - _position.z);

	float length = sqrt(distance.x*distance.x + distance.z*distance.z);

	//dedug
	float rad = 15.f;

	if (length < rad){
		return true;
	}
	else{
		return false;
	}

}