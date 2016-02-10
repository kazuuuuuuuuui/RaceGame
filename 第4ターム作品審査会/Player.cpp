//#include"Player.h"
//#include"Fire.h"
//#include"Blizzard.h"
//#include"Dash.h"
//#include"joysticManager.h"
//
//Player *player = nullptr;
//
//GLuint dashIcon = 0;
//GLuint dashGauge = 0;
//
////-------------------------------------
////自機の制御
//
//void Player::control(unsigned int _pressedKey, unsigned int _downKeys, float _x, float _y, float _z){
//
//	//エンジン音のピッチ調整
//	alSourcef(
//		m_engine->m_sid,
//		AL_PITCH,
//		pow(2, (glm::length(m_speed)*15.f) / 12));
//
//	if (false == m_isHitItem){
//
//		//前進(Aボタン)
//		if (_pressedKey & BUTTON_A){
//
//			//加速度の設定
//			//-0.005fは補正値
//			glm::vec3 accelIncrement(-0.015*sin(m_rotate.y), 0, -0.015*cos(m_rotate.y));
//			m_accel = accelIncrement;
//
//		}
//		else{
//			m_accel = { 0.f, 0.f, 0.f };
//		}
//
//		//正面右に移動
//		if (_x > 0.3){
//			m_rotate.y -= 0.02f;
//
//			_x = 1.f;
//			m_rotate.z = m_rotate.z + ((-1)*(_x / 2) - m_rotate.z)*0.1f;
//		}
//
//		//正面左に移動
//		else if (_x < -0.3){
//			m_rotate.y += 0.02f;
//
//			_x = -1.f;
//			m_rotate.z = m_rotate.z + ((-1)*(_x / 2) - m_rotate.z)*0.1f;
//		}
//		else{
//			m_rotate.z = m_rotate.z + ((_x / 2) - m_rotate.z)*0.1f;
//
//			//m_rotate.z = 0.f;
//		}
//
//		//アイテムの使用
//		if (_downKeys &  BUTTON_LB){
//
//			if (false == m_isDash){
//
//				if (hasItemNumber() > 0){
//
//					//使ったアイテムの種類によって
//					//応じたエフェクトを出す
//
//					//ファイアを使用した
//					if (FIRE == hasItemLast()){
//
//						Fire *fire = new Fire();
//						fire->m_isActive = true;
//						fire->m_basePosition = { m_position.x - sin(m_rotate.y) * 1.f, 0.5f, m_position.z - cos(m_rotate.y) * 1.f };
//						fire->m_speed = { -sin(m_rotate.y)*1.f, 0.f, -cos(m_rotate.y)*1.f };
//						effect.push_back(fire);
//						fire_ES->play();
//
//					}
//
//					//ブリザドを使用した
//					else if (BLIZZARD == hasItemLast()){
//
//						Blizzard *blizzard = new Blizzard();
//						blizzard->m_isActive = true;
//						blizzard->m_basePosition = { m_position.x + sin(m_rotate.y)*2.5f, 0.01f, m_position.z + cos(m_rotate.y)*2.5f };
//						effect.push_back(blizzard);
//
//
//					}
//
//					m_hasItem.pop_back();
//
//				}
//
//			}
//
//		}
//
//		//ダッシュ
//		if (_downKeys &  BUTTON_RB){
//
//			if (true == m_isCharged){
//
//				m_isCharged = false;
//				m_isDash = true;
//
//				m_dashPower = 0.f;
//
//				m_dashSpeed = glm::vec3(-0.09f*sin(m_rotate.y), 0.f, -0.09f*cos(m_rotate.y));
//
//				m_dash = new Dash();
//				m_dash->m_isActive = true;
//				m_dash->m_basePosition = { m_position.x, 0, m_position.z };
//				effect.push_back(m_dash);
//
//			}
//		}
//
//	}
//
//}