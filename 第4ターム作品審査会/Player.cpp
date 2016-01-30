#define BUTTON_A (1)
#define BUTTON_X (4)
#define BUTTON_Y (8)
#define BUTTON_RB (16)

#include"Player.h"
#include"Fire.h"
#include"Blizzard.h"

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

	//debug
	float speed = glm::length(m_speed);

	printf("%f\n", speed);

	//正面右に移動
	if (_x > 0.85){
		m_rotate.y -= 0.02f;
		m_rotate.z -= 0.01f*speed;
	}

	//正面左に移動
	else if (_x < -0.85){
		m_rotate.y += 0.02f;
		m_rotate.z += 0.01f*speed;
	}
	else{
		m_rotate.z = 0.f;
	}

	//アイテムの使用
	if (_downKeys &  BUTTON_RB){

		if (m_hasItem.size() > 0){

			//使ったアイテムの種類によって
			//応じたエフェクトを出す

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