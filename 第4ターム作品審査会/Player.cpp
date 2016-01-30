#define BUTTON_A (1)
#define BUTTON_X (4)
#define BUTTON_Y (8)
#define BUTTON_RB (16)

#include"Player.h"
#include"Fire.h"
#include"Blizzard.h"

Player *player = nullptr;

//-------------------------------------
//���@�̐���

void Player::control(unsigned int _pressedKey, unsigned int _downKeys, float _x, float _y, float _z){

	//�O�i(A�{�^��)
	if (_pressedKey & BUTTON_A){

		//�����x�̐ݒ�
		//-0.005f�͕␳�l
		glm::vec3 accelIncrement(-0.015*sin(m_rotate.y), 0, -0.015*cos(m_rotate.y));
		m_accel = accelIncrement;
	}
	else{
		m_accel = { 0.f, 0.f, 0.f };
	}

	//debug
	float speed = glm::length(m_speed);

	printf("%f\n", speed);

	//���ʉE�Ɉړ�
	if (_x > 0.85){
		m_rotate.y -= 0.02f;
		m_rotate.z -= 0.01f*speed;
	}

	//���ʍ��Ɉړ�
	else if (_x < -0.85){
		m_rotate.y += 0.02f;
		m_rotate.z += 0.01f*speed;
	}
	else{
		m_rotate.z = 0.f;
	}

	//�A�C�e���̎g�p
	if (_downKeys &  BUTTON_RB){

		if (m_hasItem.size() > 0){

			//�g�����A�C�e���̎�ނɂ����
			//�������G�t�F�N�g���o��

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