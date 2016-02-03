#define _USE_MATH_DEFINES
#include<math.h>
#include"Enemy.h"


//-------------------------------------
//�G��AI

void Enemy::control(){

	//��������
	//�R�[�X��AI�|�C���g��x - �G��x
	//�R�[�X��AI��z - �G��z

	glm::vec2 v = { course->m_AIPoint[m_nextPoint].m_position.x - m_position.x, course->m_AIPoint[m_nextPoint].m_position.z - m_position.z };

	v = glm::normalize(v);

	m_accel.x = v.x*0.012f;
	m_accel.z = v.y*0.012f;









	



	//�G��AI�̋�������

	if (course->m_AIPoint[m_nextPoint].checkPassFlag(m_position)){

		m_passAIPoint[m_nextPoint] = true;

		m_nextPoint++;

		if (AI_POINT_NUMBER == m_nextPoint){
			m_nextPoint = 0;
		}

		v1 = { course->m_AIPoint[m_nextPoint].m_position.x - m_position.x, course->m_AIPoint[m_nextPoint].m_position.z - m_position.z };
		v1 = glm::normalize(v1);

		//�p�x����̌����x�N�g��
		vv = { -sin(m_rotate.y), -cos(m_rotate.y) };

		tt = 0.f;

	}


	






	//�����x�N�g���ƌ������������̃x�N�g���Ƃ̍���
	glm::vec2 vvv = v1 - vv;

	vvv = vvv  * tt;

	glm::vec2 piyo = vv + vvv;

	m_rotate.y = atan2f(-piyo.x, -piyo.y);


	tt += 0.05f;
	if (tt >= 1){
		tt = 1.f;
	}

}

