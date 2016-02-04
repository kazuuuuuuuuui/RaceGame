#define _USE_MATH_DEFINES
#include<math.h>
#include"Enemy.h"
#include"Fire.h"
#include"Blizzard.h"

Enemy *com1 = nullptr;
Enemy *com2 = nullptr;
Enemy *com3 = nullptr;


//-------------------------------------
//�G��AI

void Enemy::control(){

	//��������
	//�R�[�X��AI�|�C���g��x - �G��x
	//�R�[�X��AI��z - �G��z

	glm::vec2 v = { course->m_AIPoint[m_nextPoint].m_position.x - m_position.x, course->m_AIPoint[m_nextPoint].m_position.z - m_position.z };

	v = glm::normalize(v);

	float hoge = 0.012f;

	m_accel.x = v.x*hoge;
	m_accel.z = v.y*hoge;

	//�G��AI�̋�������

	if (course->m_AIPoint[m_nextPoint].checkPassFlag(m_position)){

		m_passAIPoint[m_nextPoint] = true;

		m_nextPoint++;

		if (AI_POINT_NUMBER == m_nextPoint){
			m_nextPoint = 0;
		}

		m_pos_to_AIpoint = { course->m_AIPoint[m_nextPoint].m_position.x - m_position.x, course->m_AIPoint[m_nextPoint].m_position.z - m_position.z };
		m_pos_to_AIpoint = glm::normalize(m_pos_to_AIpoint);

		//�p�x����̌����x�N�g��
		OrientationVector = { -sin(m_rotate.y), -cos(m_rotate.y) };

		CompletionValue = 0.f;

	}

	//�����x�N�g���ƌ������������̃x�N�g���Ƃ̍���
	glm::vec2 dif = m_pos_to_AIpoint - OrientationVector;

	dif = dif  * CompletionValue;

	//���g�̌����x�N�g���ɍ����𑫂����x�N�g��
	glm::vec2 OrientationVectorPulsDif = OrientationVector + dif;

	m_rotate.y = atan2f(-OrientationVectorPulsDif.x, -OrientationVectorPulsDif.y);

	//�C���N�������g����l�ɂ����
	//�⊮�̊��炩�����ς��
	CompletionValue += 0.05f;

	if (CompletionValue >= 1){
		CompletionValue = 1.f;
	}

}

//-------------------------------------
//�A�C�e���������Ă��ۂɃA�C�e�����g�p����
//20�b��1��g�p�̃`�F�b�N���s��

void Enemy::useItem(){

	if (0 == m_flame % 60 * 20){

		if (hasItemNumber() > 0){

			//�t�@�C�A���g�p����
			if (FIRE == hasItemLast()){

				Fire *fire = new Fire();
				fire->m_isActive = true;
				fire->m_basePosition = { m_position.x - sin(m_rotate.y) * 1.f, 0.5f, m_position.z - cos(m_rotate.y) * 1.f };
				fire->m_speed = { -sin(m_rotate.y)*1.f, 0.f, -cos(m_rotate.y)*1.f };
				effect.push_back(fire);

			}

			//�u���U�h���g�p����
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

