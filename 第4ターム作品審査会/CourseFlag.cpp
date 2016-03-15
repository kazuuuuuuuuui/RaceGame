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
		glTranslatef(m_position.m_x, m_position.m_y, m_position.m_z);
		glRotatef(90, 1, 0, 0);
		Circle2D(20, 0, 0);
		glutSolidCube(0.5);
	}
	glPopMatrix();
}


//周回判定をとるためのコースフラグを通っているか判定する


bool CourseFlag::checkPassFlag(oka::Vec3 _position){

	oka::Vec3 distance;

	distance.m_x = (m_position.m_x - _position.m_x);
	distance.m_y=0;
	distance.m_z = (m_position.m_z - _position.m_z);

	float length = sqrt(distance.m_x*distance.m_x + distance.m_z*distance.m_z);

	float rad = 20.f;

	if (length < rad){
		return true;
	}
	else{
		return false;
	}

}