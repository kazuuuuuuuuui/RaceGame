#define _USE_MATH_DEFINES
#include<math.h>
#include"Enemy.h"
#include"Fire.h"
#include"Blizzard.h"

Enemy *com1 = nullptr;
Enemy *com2 = nullptr;
Enemy *com3 = nullptr;


//-------------------------------------
//敵のAI

void Enemy::control(){

	//向き調整
	//コースのAIポイントのx - 敵のx
	//コースのAIのz - 敵のz

	glm::vec2 v = { course->m_AIPoint[m_nextPoint].m_position.x - m_position.x, course->m_AIPoint[m_nextPoint].m_position.z - m_position.z };

	v = glm::normalize(v);

	float hoge = 0.012f;

	m_accel.x = v.x*hoge;
	m_accel.z = v.y*hoge;

	//敵のAIの挙動制御

	if (course->m_AIPoint[m_nextPoint].checkPassFlag(m_position)){

		m_passAIPoint[m_nextPoint] = true;

		m_nextPoint++;

		if (AI_POINT_NUMBER == m_nextPoint){
			m_nextPoint = 0;
		}

		m_pos_to_AIpoint = { course->m_AIPoint[m_nextPoint].m_position.x - m_position.x, course->m_AIPoint[m_nextPoint].m_position.z - m_position.z };
		m_pos_to_AIpoint = glm::normalize(m_pos_to_AIpoint);

		//角度からの向きベクトル
		OrientationVector = { -sin(m_rotate.y), -cos(m_rotate.y) };

		CompletionValue = 0.f;

	}

	//向きベクトルと向けたい方向のベクトルとの差分
	glm::vec2 dif = m_pos_to_AIpoint - OrientationVector;

	dif = dif  * CompletionValue;

	//自身の向きベクトルに差分を足したベクトル
	glm::vec2 OrientationVectorPulsDif = OrientationVector + dif;

	m_rotate.y = atan2f(-OrientationVectorPulsDif.x, -OrientationVectorPulsDif.y);

	//インクリメントする値によって
	//補完の滑らかさが変わる
	CompletionValue += 0.05f;

	if (CompletionValue >= 1){
		CompletionValue = 1.f;
	}

}

//-------------------------------------
//アイテムを持ってた際にアイテムを使用する
//20秒に1回使用のチェックを行う

void Enemy::useItem(){

	if (0 == m_flame % 60 * 20){

		if (hasItemNumber() > 0){

			//ファイアを使用した
			if (FIRE == hasItemLast()){

				Fire *fire = new Fire();
				fire->m_isActive = true;
				fire->m_basePosition = { m_position.x - sin(m_rotate.y) * 1.f, 0.5f, m_position.z - cos(m_rotate.y) * 1.f };
				fire->m_speed = { -sin(m_rotate.y)*1.f, 0.f, -cos(m_rotate.y)*1.f };
				effect.push_back(fire);

			}

			//ブリザドを使用した
			else if (BLIZZARD == hasItemLast()){

				Blizzard *blizzard = new Blizzard();
				blizzard->m_isActive = true;
				blizzard->m_basePosition = { m_position.x + sin(m_rotate.y)*2.5f, 0.01f, m_position.z + cos(m_rotate.y)*2.5f };
				effect.push_back(blizzard);


			}

			m_hasItem.pop_back();



		}
	}
}

