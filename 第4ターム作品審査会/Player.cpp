#define BUTTON_A (1)
#define BUTTON_X (4)
#define BUTTON_Y (8)
#define BUTTON_RB (16)

#include"Player.h"

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

	//���ʉE�Ɉړ�
	if (_x > 0.9){
		m_rotate.y -= 0.02f;

	}

	//���ʍ��Ɉړ�
	if (_x < -0.9){
		m_rotate.y += 0.02f;
	}

	//�A�C�e���̎g�p
	//if (_downKeys &  BUTTON_RB){

	//	//��芸����
	//	//�t�@�C�A
	//	FireEffect *fire[PARTICLE_NUNBER] = { nullptr };

	//	for (int i = 0; i < PARTICLE_NUNBER; i++){
	//		fire[i] = new FireEffect();
	//		fire[i]->m_position = m_position;
	//		m_useFire.push_back(fire[i]);
	//	}



	//	//�������Ă���A�C�e���̌��𒲂�
	//	//�A�C�e�������Ă��Ȃ�������(0)�������Ȃ�
	//	/*if (0 != hasMagicStoneNumber()){



	//	}
	//	else{}*/

	//}

}