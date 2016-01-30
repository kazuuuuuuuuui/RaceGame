#define _USE_MATH_DEFINES
#include<math.h>
#include"AIFlag.h"
#include"CourseFlag.h"

void AIFlag::draw(){
	glPushMatrix();
	{
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(90, 1, 0, 0);
		Circle2D(15, 0, 0);
	}
	glPopMatrix();

	glPushMatrix(); 
	{
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glutSolidTeapot(0.5);
	}
	glPopMatrix();
}


//周回判定をとるためのコースフラグを通っているか判定する


bool AIFlag::checkPassFlag(glm::vec3 _position){

	glm::vec3 distance;

	distance.x = (m_position.x - _position.x);
	distance.y = 0;
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