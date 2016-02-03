#define _USE_MATH_DEFINES
#include<math.h>
#include"Enemy.h"


//-------------------------------------
//敵のAI

void Enemy::control(){

	//向き調整
	//コースのAIポイントのx - 敵のx
	//コースのAIのz - 敵のz

	glm::vec2 v = { course->m_AIPoint[m_nextPoint].m_position.x - m_position.x, course->m_AIPoint[m_nextPoint].m_position.z - m_position.z };

	v = glm::normalize(v);

	m_accel.x = v.x*0.012f;
	m_accel.z = v.y*0.012f;









	



	//敵のAIの挙動制御

	if (course->m_AIPoint[m_nextPoint].checkPassFlag(m_position)){

		m_passAIPoint[m_nextPoint] = true;

		m_nextPoint++;

		if (AI_POINT_NUMBER == m_nextPoint){
			m_nextPoint = 0;
		}

		v1 = { course->m_AIPoint[m_nextPoint].m_position.x - m_position.x, course->m_AIPoint[m_nextPoint].m_position.z - m_position.z };
		v1 = glm::normalize(v1);

		//角度からの向きベクトル
		vv = { -sin(m_rotate.y), -cos(m_rotate.y) };

		tt = 0.f;

	}


	






	//向きベクトルと向けたい方向のベクトルとの差分
	glm::vec2 vvv = v1 - vv;

	vvv = vvv  * tt;

	glm::vec2 piyo = vv + vvv;

	m_rotate.y = atan2f(-piyo.x, -piyo.y);


	tt += 0.05f;
	if (tt >= 1){
		tt = 1.f;
	}

}

