#include"Player.h"
#include"Fire.h"
#include"Blizzard.h"
#include"Dash.h"
#include"joysticManager.h"

Player *player = nullptr;

GLuint dashIcon = 0;
GLuint dashGauge = 0;

//-------------------------------------
//���@�̐���

void Player::control(unsigned int _pressedKey, unsigned int _downKeys, float _x, float _y, float _z){

	if (false == m_isHitItem){

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
		if (_x > 0.3){
			m_rotate.y -= 0.02f;

			_x = 1.f;
			m_rotate.z = m_rotate.z + ((-1)*(_x / 2) - m_rotate.z)*0.1f;
		}

		//���ʍ��Ɉړ�
		else if (_x < -0.3){
			m_rotate.y += 0.02f;

			_x = -1.f;
			m_rotate.z = m_rotate.z + ((-1)*(_x / 2) - m_rotate.z)*0.1f;
		}
		else{
			m_rotate.z = m_rotate.z + ((_x / 2) - m_rotate.z)*0.1f;

			//m_rotate.z = 0.f;
		}

		//�A�C�e���̎g�p
		if (_downKeys &  BUTTON_LB){

			if (false == m_isDash){

				if (hasItemNumber() > 0){

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

		//�_�b�V��
		if (_downKeys &  BUTTON_RB){

			if (m_dashPower == 90){

				m_isDash = true;

				m_dashPower = 0.f;

				m_dashSpeed = glm::vec3(-0.09f*sin(m_rotate.y), 0.f, -0.09f*cos(m_rotate.y));

				m_dash = new Dash();
				m_dash->m_isActive = true;
				m_dash->m_basePosition = { m_position.x, 0, m_position.z };
				effect.push_back(m_dash);

			}
		}

	}

}


//-------------------------------------
//�_�b�V���Q�[�W�̃C���^�[�t�F�C�X

void Player::printDashGauge(){

	//�C���^�[�t�F�C�X����
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//�A�C�R������
	glPushMatrix();
	{
		glTranslatef(5, 255, 0);

		glBindTexture(GL_TEXTURE_2D, dashIcon);

		glBegin(GL_QUADS);
		{
			glColor4f(1, 1, 1, 1);
			glTexCoord2f(0, 1); glVertex2f(0, 0);
			glTexCoord2f(1, 1); glVertex2f(40, 0);
			glTexCoord2f(1, 0); glVertex2f(40, 40);
			glTexCoord2f(0, 0); glVertex2f(0, 40);
		}
		glEnd();
	}
	glPopMatrix();

	//�Q�[�W�O�g
	glPushMatrix();
	{
		glTranslatef(42, 266, 0);

		glBindTexture(GL_TEXTURE_2D, dashGauge);

		glBegin(GL_QUADS);
		{
			glColor4f(1, 1, 1, 1);
			glTexCoord2f(0, 0); glVertex2f(0, 0);
			glTexCoord2f(1, 0); glVertex2f(100, 0);
			glTexCoord2f(1, 1); glVertex2f(100, 15);
			glTexCoord2f(0, 1); glVertex2f(0, 15);
		}
		glEnd();
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	//�Q�[�W����

	glPushMatrix();
	{
		glTranslatef(46.5, 270.f, 0);

		glBegin(GL_QUADS);
		{
			if (DASH_GAUGE_MAX == m_dashPower){
				glColor3f(1, rand() % 256 / 255.f, rand() % 256 / 255.f);
			}
			else{
				glColor3f(1, 0, 0);
			}
			glVertex2f(0, 0);
			glVertex2f(m_dashPower, 0);
			glVertex2f(m_dashPower, 7.f);
			glVertex2f(0, 7.f);
		}
		glEnd();

	}
	glPopMatrix();

}