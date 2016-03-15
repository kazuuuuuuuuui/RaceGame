#define _USE_MATH_DEFINES
#include<math.h>
#include"Vec3.h"
#include"AIFlag.h"
#include"CourseFlag.h"

void AIFlag::draw(){
	glPushMatrix();
	{
		glTranslatef(m_position.m_x, m_position.m_y, m_position.m_z);
		glRotatef(90, 1, 0, 0);
		Circle2D(15, 0, 0);
	}
	glPopMatrix();

	glPushMatrix(); 
	{
		glTranslatef(m_position.m_x, m_position.m_y, m_position.m_z);
		glutSolidTeapot(0.5);
	}
	glPopMatrix();
}



bool AIFlag::checkPassFlag(oka::Vec3 _position){

	oka::Vec3 distance;

	distance.m_x = (m_position.m_x - _position.m_x);
	distance.m_y = 0;
	distance.m_z = (m_position.m_z - _position.m_z);

	float length = sqrt(distance.m_x*distance.m_x + distance.m_z*distance.m_z);

	//dedug
	float rad = 15.f;

	if (length < rad){
		return true;
	}
	else{
		return false;
	}

}