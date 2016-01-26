#define BUTTON_A (1)
#define BUTTON_X (4)
#define BUTTON_Y (8)
#define BUTTON_RB (16)

#include"Player.h"

Player *player = nullptr;

//-------------------------------------
//自機の制御

void Player::control(unsigned int _pressedKey, unsigned int _downKeys, float _x, float _y, float _z){

	//前進(Aボタン)
	if (_pressedKey & BUTTON_A){

		//加速度の設定
		//-0.005fは補正値
		glm::vec3 accelIncrement(-0.015*sin(m_rotate.y), 0, -0.015*cos(m_rotate.y));
		m_accel = accelIncrement;
	}
	else{
		m_accel = { 0.f, 0.f, 0.f };
	}

	//正面右に移動
	if (_x > 0.9){
		m_rotate.y -= 0.02f;
		m_rotate.z += 0.005f;
	}

	//正面左に移動
	else if (_x < -0.9){
		m_rotate.y += 0.02f;
		m_rotate.z -= 0.005f;
	}
	else{
		m_rotate.z = 0.f;
	}

	//アイテムの使用
	if (_downKeys &  BUTTON_RB){

		if (m_hasItem.size() > 0){
			m_hasItem.pop_back();
		}

	}

}