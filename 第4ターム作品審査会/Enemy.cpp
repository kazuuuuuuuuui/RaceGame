#define _USE_MATH_DEFINES
#include<math.h>
#include"Enemy.h"



//-------------------------------------
//�G��AI

void Enemy::control(){

	//�R�[�X��AI�|�C���g��x - �G��x
	//�R�[�X��AI��z - �G��z

	glm::vec2 v = { course->m_AIPoint[m_nextPoint].m_position.x - m_position.x, course->m_AIPoint[m_nextPoint].m_position.z - m_position.z };

	v = glm::normalize(v);

	m_rotate.y = (M_PI + atan2f(v.x, v.y));

	m_accel.x = v.x*0.012f;
	m_accel.z = v.y*0.012f;

}

