#include"Character.h"
#include<stdio.h>

#define _USE_MATH_DEFINES
#include<math.h>
#include"GameManager.h"
#include"Course.h"
#include"Character.h"
#include"Item.h"
#include"camera.h"
#include"BmpImage.h"
#include"Material.h"
#include"Fire.h"
#include"Blizzard.h"
#include"StrokeString.h"
#include"SoundManager.h"
#include"RaceManager.h"
#include"ImageManager.h"
#include"JoysticManager.h"
#include"CharacterManager.h"
#include"TimeManager.h"
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtx\transform.hpp"
#include"glut.h"

//-------------------------------------
//���@�̍X�V
//�S�[���������_�ōX�V���~�߂�

void Character::Update(){

	//if (false == m_isGoal)
	//{
		//�t���[���̊Ǘ�
		m_flame++;

		m_lapTimeCounter++;

		//�~���b
		m_milliSecond = oka::TimeManager::GetInstance()->GetMilliSecond(m_flame);
		m_lapMilliSecond[m_lapCount] = oka::TimeManager::GetInstance()->GetMilliSecond(m_lapTimeCounter);

		//�b
		m_second = oka::TimeManager::GetInstance()->GetSecond(m_flame);
		m_lapSecond[m_lapCount] = oka::TimeManager::GetInstance()->GetSecond(m_lapTimeCounter);

		//��
		m_minute = oka::TimeManager::GetInstance()->GetMinutes(m_second);
		m_lapMinute[m_lapCount] = oka::TimeManager::GetInstance()->GetMinutes(m_lapSecond[m_lapCount]);

		m_second = m_second % 60;
		m_lapSecond[m_lapCount] = m_lapSecond[m_lapCount] % 60;

		sprintf_s(m_totalTime, "%02d:%02d:%03d", m_minute, m_second, m_milliSecond);


		sprintf_s(m_lap, "%d", (m_lapCount + 1));

		//�_�b�V���Q�[�W�̉�
		m_dashPower += 0.1f;

		if (m_dashPower >= DASH_GAUGE_MAX)
		{
			m_dashPower = DASH_GAUGE_MAX;

			if (false == m_isCharged)
			{
				m_isCharged = true;
				oka::SoundManager::GetInstance()->Play("chargeComplete");
			}

		}


		//1���������̔���
		if (countLap()){

			//�t���[���̏�����
			m_lapTimeCounter = 0;

			//�`�F�b�N�|�C���g�̏�����
			for (int i = 0; i < Course::checkPointNum; i++)
			{
				m_passCheckPoint[i] = false;
			}

			//AI�|�C���g�̏�����
			for (int i = 0; i < Course::aimPointNum; i++)
			{
				m_passAIPoint[i] = false;
			}

			m_nowPoint = 0;

			sprintf_s(m_lapTime[FIRST], "%02d:%02d:%03d ", m_lapMinute[FIRST], m_lapSecond[FIRST], m_lapMilliSecond[FIRST]);
			sprintf_s(m_lapTime[SECOND], "%02d:%02d:%03d ", m_lapMinute[SECOND], m_lapSecond[SECOND], m_lapMilliSecond[SECOND]);
			sprintf_s(m_lapTime[THIRD], "%02d:%02d:%03d ", m_lapMinute[THIRD], m_lapSecond[THIRD], m_lapMilliSecond[THIRD]);

			m_lapCount++;

			if (m_contoroller.m_isConnect)
			{
				//1���ڂ܂���2���ڂ̎��̂ݖ炷
				if (1 == m_lapCount)
				{
					oka::SoundManager::GetInstance()->Play("lapCountSE");
				}
				else if (2 == m_lapCount)
				{
					oka::SoundManager::GetInstance()->Play("finalLapSE");
			
				}
			}

		}

	//}

	//�s��v�Z
	oka::Mat4x4 translate = oka::Mat4x4::Translate(oka::Vec3(m_transform.GetPosition().m_x, m_transform.GetPosition().m_y, m_transform.GetPosition().m_z));
	oka::Mat4x4 rotate = oka::Mat4x4::RotateY(m_transform.GetRotation().m_y + m_crashRotate)*oka::Mat4x4::RotateZ(m_transform.GetRotation().m_z);
	oka::Mat4x4 scale = oka::Mat4x4::Scale(m_transform.GetScale());

	//�e�̍s��
	m_matrix = translate *rotate *scale;

	//�ԑ�
	m_body.m_matrix = m_matrix;

	//�O��
	m_frontWheel.m_transform.SetPositionX(0.0f);
	m_frontWheel.m_transform.SetPositionY(2.8f);
	m_frontWheel.m_transform.SetPositionZ(-9.0f);
	m_frontWheel.m_transform.SetRotation(m_transform.GetRotation());

	m_frontWheel.m_matrix = m_matrix;

	//���
	m_backWheel.m_transform.SetPositionX(0.0f);
	m_backWheel.m_transform.SetPositionY(3.1f);
	m_backWheel.m_transform.SetPositionZ(6.3f);
	m_backWheel.m_transform.SetRotation(m_transform.GetRotation());

	m_backWheel.m_matrix = m_matrix;

	//�O�֍��W
	//m_frontPosition.m_x = m_transform.GetPosition().m_x - sin(m_transform.GetRotation().m_y)*1.1f;
	//m_frontPosition.m_y = 0.5f;
	//m_frontPosition.m_z = m_transform.GetPosition().m_z - cos(m_transform.GetRotation().m_y)*1.1f;

	////��֍��W
	//m_backPosition.m_x = m_transform.GetPosition().m_x + sin(m_transform.GetRotation().m_y)*0.7f;
	//m_backPosition.m_y = 0.5f;
	//m_backPosition.m_z = m_transform.GetPosition().m_z + cos(m_transform.GetRotation().m_y)*0.7f;

	//�X�s�[�h�E�|�W�V�����̍X�V
	m_speed += (m_dashSpeed + m_accel);

	m_transform.SetPosition(m_transform.GetPosition() + m_speed);


	//���̍X�V
	m_smoke.Update();
	m_smoke.m_basePosition.m_x = m_transform.GetPosition().m_x + sin(m_transform.GetRotation().m_y)*1.7f;
	m_smoke.m_basePosition.m_y = 0.5f;
	m_smoke.m_basePosition.m_z = m_transform.GetPosition().m_z + cos(m_transform.GetRotation().m_y)*1.7f;

	//���������銵��
	m_speed *= 0.965f;

	//�_�b�V���̌�������
	m_dashSpeed *= 0.96;

	if (m_dashSpeed.length() <= 0.0001)
	{
		//�_�b�V����ԉ���
		m_isDash = false;
	}
	

	//�ԗւ̉�]�X�s�[�h�X�V
	//*100�͕␳�l
	m_wheelSpeed = m_speed.length() * 100.f;


	//�X���b�v����
	slip();

	//�`�F�b�N�|�C���g��ʉ߂��Ă��邩�̔��菈��
	for (int i = 0; i < Course::checkPointNum; i++)
	{
		if (0 == i)
		{
			if (false == m_passCheckPoint[i] && RaceManager::GetInstance()->m_course->m_checkPoint[i].CheckPass(m_transform.GetPosition())){

				m_passCheckPoint[i] = true;
				m_nowPoint++;

			}

		}

		else
		{

			if (true == m_passCheckPoint[i - 1])
			{

				if (false == m_passCheckPoint[i] && RaceManager::GetInstance()->m_course->m_checkPoint[i].CheckPass(m_transform.GetPosition()))
				{
					m_passCheckPoint[i] = true;
					m_nowPoint++;
				}
			}
		}

	}

	//�ڎw���Ă���`�F�b�N�|�C���g�ւ̋����̍X�V
	m_nextCheckPointLength = checkNextCheckPointLength();

	//����̃R�[�X�̈悩��o�Ă��Ȃ����̔���
	checkCourseOut();

	//�_�[�g�ɓ��������̔���Ə���
	if (inDart()){
		m_speed *= 0.9f;
	}

	//�S�[���������̔���
	if (false == m_isGoal && checkIsGoal())
	{
		m_isGoal = true;
		m_lastRanking = m_ranking;

		oka::SoundManager::GetInstance()->Play("goalSE");
	}

}

//-------------------------------------
//���@�̕`��

void Character::Draw()
{
	//�ԑ�
	m_body.Draw();

	//�O��
	//m_frontWheel.Draw();

	//���
	//m_backWheel.Draw();

	//�ԑ̉e
	//m_body.DrawShadow();

	////�e���`��
	////���
	//glPushMatrix();
	//{
	//	//�q���̍s��
	//	glm::mat4 child = glm::scale(glm::vec3(0.92f, 0, 0.92f));
	//	//�I�t�Z�b�g
	//	glm::mat4 offSet = glm::translate(glm::vec3(0.0f, 0.01f, 6.3f));
	//	glm::mat4 myMatrix = m_matrix * offSet *child;
	//	glMultMatrixf((GLfloat*)&myMatrix);
	//	std::vector<float>::iterator itr_v = m_backWheel.m_vertex.begin();
	//	glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));
	//	std::vector<unsigned short>::iterator itr_i = m_backWheel.m_index.begin();
	//	/*��֕`��*/
	//	glDrawElements(GL_TRIANGLES, m_backWheel.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));
	//}
	//glPopMatrix();

}



//-------------------------------------
//�������Ă���A�C�e���̕`��

void Character::drawHasItem()
{
	for (unsigned int i = 0; i < m_hasItem.size(); i++)
	{

		//�e�N�X�`���̐ݒ�
		switch (m_hasItem[i]){
		case FIRE:

			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("ItemFire"));

			break;

		case BLIZZARD:

			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("ItemBlizzard"));

			break;

		}


		glPushMatrix();
		{
			glTranslatef(m_transform.GetPosition().m_x + sin(m_transform.GetRotation().m_y) * 2.8 + sin(m_transform.GetRotation().m_y)*i,
				0.5f,
				m_transform.GetPosition().m_z + cos(m_transform.GetRotation().m_y) * 2.8 + cos(m_transform.GetRotation().m_y)*i);

			glColor3f(1, 1, 1);

			double s, t0, t1, r0, r1, th0, th1, phi;
			double p[2][3];

			for (int j = 0; j < ITEM_STACK; j++){
				t0 = (double)j / (double)ITEM_STACK;
				t1 = (double)(j + 1) / (double)ITEM_STACK;
				th0 = M_PI * t0;
				th1 = M_PI * t1;
				r0 = ITEM_RADIUS * sin(th0);
				r1 = ITEM_RADIUS * sin(th1);
				p[0][2] = ITEM_RADIUS * cos(th0);
				p[1][2] = ITEM_RADIUS * cos(th1);

				t0 = (1.0 - t0) * ITEM_REPEAT_T;
				t1 = (1.0 - t1) * ITEM_REPEAT_T;

				glEnable(GL_TEXTURE_2D);

				glBegin(GL_QUAD_STRIP);
				for (int i = 0; i <= ITEM_SLICE; i++){
					s = (double)i / (double)ITEM_SLICE;
					phi = 2.0 * M_PI * s;
					p[0][0] = -r0 * cos(phi);
					p[0][1] = -r0 * sin(phi);
					p[1][0] = -r1 * cos(phi);
					p[1][1] = -r1 * sin(phi);

					s *= ITEM_REPEAT_S;

					glTexCoord2d(s, t0);
					glNormal3dv(p[0]);
					glVertex3dv(p[0]);

					glTexCoord2d(s, t1);
					glNormal3dv(p[1]);
					glVertex3dv(p[1]);
				}
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

		}
		glPopMatrix();

	}

}

//-------------------------------------
//���@�̐���

void Character::control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY)
{
	//�G���W�����̃s�b�`����

	oka::SoundManager::GetInstance()->ChangeVolume("Engine", pow(2, (m_speed.length()*15.f) / 12));

	if (false == m_isHitItem)
	{

		//�O�i(A�{�^��)
		if (_pressedKey & XINPUT_GAMEPAD_A)
		{
			//�����x�̐ݒ�
			//-0.005f�͕␳�l
			oka::Vec3 accelIncrement(-0.015*sin(m_transform.GetRotation().m_y), 0.f, -0.015*cos(m_transform.GetRotation().m_y));
			m_accel = accelIncrement;
	
		}
		else
		{
			m_accel = { 0.f, 0.f, 0.f };
		}

		//���ʉE�Ɉړ�
		if (_sThumbLX > 0.3)
		{
			m_transform.SetRotationY(m_transform.GetRotation().m_y-0.02f);

			_sThumbLX = 1.f;
			m_transform.SetRotationZ(m_transform.GetRotation().m_z + ((-1)*(_sThumbLX / 2) - m_transform.GetRotation().m_z)*0.1f);
		}

		//���ʍ��Ɉړ�
		else if (_sThumbLX < -0.3)
		{
	
			m_transform.SetRotationY(m_transform.GetRotation().m_y + 0.02f);

			_sThumbLX = -1.f;
			m_transform.SetRotationZ(m_transform.GetRotation().m_z + ((-1)*(_sThumbLX / 2) - m_transform.GetRotation().m_z)*0.1f);
		}
		else
		{
			m_transform.SetRotationZ(m_transform.GetRotation().m_z + ((_sThumbLX / 2) - m_transform.GetRotation().m_z)*0.1f);
		}

		//�A�C�e���̎g�p
		if (_downKeys &  XINPUT_GAMEPAD_LEFT_SHOULDER)
		{

			if (false == m_isDash)
			{

				if (hasItemNumber() > 0)
				{

					//�g�����A�C�e���̎�ނɂ����
					//�������G�t�F�N�g���o��

					//�t�@�C�A���g�p����
					if (FIRE == hasItemLast())
					{
						Fire *fire = new Fire();
						fire->m_isActive = true;
						fire->m_basePosition = { m_transform.GetPosition().m_x - sin(m_transform.GetRotation().m_y) * 1.f, 0.5f,m_transform.GetPosition().m_z - cos(m_transform.GetRotation().m_y) * 1.f };
						fire->m_speed = { -sin(m_transform.GetRotation().m_y)*1.f, 0.f, -cos(m_transform.GetRotation().m_y)*1.f };
						oka::GameManager::GetInstance()->AddGameObject(fire);
						oka::SoundManager::GetInstance()->Play("fireSE");

					}

					//�u���U�h���g�p����
					else if (BLIZZARD == hasItemLast())
					{

						Blizzard *blizzard = new Blizzard();
						blizzard->m_isActive = true;
						blizzard->m_basePosition = { m_transform.GetPosition().m_x + sin(m_transform.GetRotation().m_y)*2.5f, 0.01f, m_transform.GetPosition().m_z + cos(m_transform.GetRotation().m_y)*2.5f };
						oka::GameManager::GetInstance()->AddGameObject(blizzard);
					}

					m_hasItem.pop_back();

				}

			}

		}

		//�_�b�V��
		if (_downKeys &  XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{
			if (true == m_isCharged)
			{

				m_isCharged = false;
				m_isDash = true;

				m_dashPower = 0.0f;

				m_dashSpeed = oka::Vec3(-0.09f*sin(m_transform.GetRotation().m_y), 0.f, -0.09f*cos(m_transform.GetRotation().m_y));

			}
		}

	}

}




//-------------------------------------
//�G��AI

void Character::control()
{

	//��������
	//�R�[�X��AI�|�C���g��x - �G��x
	//�R�[�X��AI��z - �G��z

	glm::vec2 v = { RaceManager::GetInstance()->m_course->m_aimPoint[m_nextPoint].m_position.m_x - m_transform.GetPosition().m_x,
		RaceManager::GetInstance()->m_course->m_aimPoint[m_nextPoint].m_position.m_z - m_transform.GetPosition().m_z };

	v = glm::normalize(v);

	//0.�`0.018�ڈ�
	float sp = (((float)rand() / RAND_MAX) / 1000) * 28;

	m_accel.m_x = v.x*sp;
	m_accel.m_z = v.y*sp;

	//�G��AI�̋�������

	if (RaceManager::GetInstance()->m_course->m_aimPoint[m_nextPoint].CheckPass(m_transform.GetPosition())){

		m_passAIPoint[m_nextPoint] = true;

		m_nextPoint++;

		if (Course::aimPointNum == m_nextPoint){
			m_nextPoint = 0;
		}

		m_pos_to_AIpoint = { RaceManager::GetInstance()->m_course->m_aimPoint[m_nextPoint].m_position.m_x - m_transform.GetPosition().m_x,
			RaceManager::GetInstance()->m_course->m_aimPoint[m_nextPoint].m_position.m_z - m_transform.GetPosition().m_z };
		m_pos_to_AIpoint = glm::normalize(m_pos_to_AIpoint);

		//�p�x����̌����x�N�g��
		OrientationVector = { -sin(m_transform.GetRotation().m_y), -cos(m_transform.GetRotation().m_y) };

		CompletionValue = 0.f;

	}

	//�����x�N�g���ƌ������������̃x�N�g���Ƃ̍���
	glm::vec2 dif = m_pos_to_AIpoint - OrientationVector;

	dif = dif  * CompletionValue;

	//���g�̌����x�N�g���ɍ����𑫂����x�N�g��
	glm::vec2 OrientationVectorPulsDif = OrientationVector + dif;

	m_transform.SetRotationY(atan2f(-OrientationVectorPulsDif.x, -OrientationVectorPulsDif.y));

	//�C���N�������g����l�ɂ����
	//�⊮�̊��炩�����ς��
	CompletionValue += 0.05f;

	if (CompletionValue >= 1){
		CompletionValue = 1.f;
	}


	//�A�C�e�����g�p���邩�̏���
	useItem();

}

//-------------------------------------
//�A�C�e���������Ă��ۂɃA�C�e�����g�p����
//20�b��1��g�p�̃`�F�b�N���s��

void Character::useItem(){

	if (0 == m_flame % 60 * 20)
	{
		if (hasItemNumber() > 0)
		{
			//�t�@�C�A���g�p����
			if (FIRE == hasItemLast())
			{
				Fire *fire = new Fire();
				fire->m_isActive = true;
				fire->m_basePosition = { m_transform.GetPosition().m_x - sin(m_transform.GetRotation().m_y) * 1.f, 0.5f, m_transform.GetPosition().m_z - cos(m_transform.GetRotation().m_y) * 1.f };
				fire->m_speed = { -sin(m_transform.GetRotation().m_y)*1.f, 0.f, -cos(m_transform.GetRotation().m_y)*1.f };
				oka::GameManager::GetInstance()->AddGameObject(fire);
			}

			//�u���U�h���g�p����
			else if (BLIZZARD == hasItemLast())
			{

				Blizzard *blizzard = new Blizzard();
				blizzard->m_isActive = true;
				blizzard->m_basePosition = { m_transform.GetPosition().m_x + sin(m_transform.GetRotation().m_y)*2.5f, 0.01f, m_transform.GetPosition().m_z + cos(m_transform.GetRotation().m_y)*2.5f };
				oka::GameManager::GetInstance()->AddGameObject(blizzard);

			}

			m_hasItem.pop_back();



		}
	}
}

//-------------------------------------
//����̃R�[�X�̈悩��o�Ă��Ȃ����̔��f��
//�o�Ă����ꍇ�̉����߂�����

void Character::checkCourseOut()
{

	if (m_transform.GetPosition().m_x < 0.0f)
	{
		m_transform.SetPositionX(0.0f);
	}

	if (m_transform.GetPosition().m_x > COURSE_WIDTH)
	{
		m_transform.SetPositionX(COURSE_WIDTH);
	}

	if (m_transform.GetPosition().m_z > 0.0f)
	{
		m_transform.SetPositionZ(0.0f);
	}

	//256�̂܂܂���256�Ԗڂ̃s�N�Z�����ɃA�N�Z�X���Ă��܂��̂ŕ␳�l+1���Ă���
	if (m_transform.GetPosition().m_z < 1-COURSE_HEIGHT)
	{
		m_transform.SetPositionZ(1 - COURSE_HEIGHT);
	}

}


//-------------------------------------
//�ڎw���Ă���`�F�b�N�|�C���g�܂ł̋�����Ԃ�

float Character::checkNextCheckPointLength()
{
	oka::Vec3 v;

	v = m_transform.GetPosition() - RaceManager::GetInstance()->m_course->m_checkPoint[m_nowPoint].m_position;

	return v.length();
}

//-------------------------------------
//�v���C���[���_�[�g�ɓ����Ă��邩����
//�����Ă�����true �����Ă��Ȃ�������false��Ԃ�

bool Character::inDart()
{

	//�v���C���[���ǂ̃s�N�Z����ɂ��邩���f��
	//�����̃s�N�Z�����ɂ���Ĕ��肷��

	if (RaceManager::GetInstance()->m_course->m_buffer[COURSE_HEIGHT - 1 + (int)m_transform.GetPosition().m_z][(int)m_transform.GetPosition().m_x] == DART){

		return true;

	}
	else{

		return false;

	}
}

//-------------------------------------
//�A�C�e���ɓ����������̃X���b�v����

void Character::slip()
{

	if (m_isHitItem)
	{
		m_speed = { 0.0f, 0.0f, 0.0f };
		
	}

	m_crashRotate *= 0.9f;

	if (m_crashRotate < 0.5f)
	{
		m_isHitItem = false;

	}


}

//-------------------------------------
//���ʂ̕`��

void Character::printRanking()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		{

			if (false == m_isGoal)
			{
				//���ʂɉ����ē\��e�N�X�`����ς���
				switch (m_ranking)
				{
				case 1:
					glColor4f(255 / 255.f, 201 / 255.f, 14 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank1st"));
					break;

				case 2:
					glColor4f(255 / 255.f, 255 / 255.f, 255 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank2nd"));
					break;

				case 3:
					glColor4f(188 / 255.f, 126 / 255.f, 92 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank3rd"));
					break;

				case 4:
					glColor4f(0 / 255.f, 255 / 255.f, 0 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank4th"));
					break;

				}

				glTranslatef(0.f, 0.f, 0);

			}

			else
			{
				//���ʂɉ����ē\��e�N�X�`����ς���
				switch (m_lastRanking) {
				case 1:
					glColor4f(255 / 255.f, 201 / 255.f, 14 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank1st"));
					break;

				case 2:
					glColor4f(255 / 255.f, 255 / 255.f, 255 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank2nd"));
					break;

				case 3:
					glColor4f(188 / 255.f, 126 / 255.f, 92 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank3rd"));
					break;

				case 4:
					glColor4f(0 / 255.f, 255 / 255.f, 0 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank4th"));
					break;

				}

				glTranslatef(50.f, 193.f, 0);

			}


			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex2f(0, 0);

				glTexCoord2f(1, 1);
				glVertex2f(80, 0);

				glTexCoord2f(1, 0);
				glVertex2f(80, 80);

				glTexCoord2f(0, 0);
				glVertex2f(0, 80);
			}
			glEnd();
		}
		glPopMatrix();

	}
	glPopAttrib();

}

//-------------------------------------
//GOAL�̕`��

void printGoal()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	{

		glTranslatef(140, 185, 0);

		glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Goal"));

		glBegin(GL_QUADS);
		{
			glColor4f(1, 0, 0, 1);
			glTexCoord2f(0, 1); glVertex2f(0, 0);
			glTexCoord2f(1, 1); glVertex2f(150, 0);
			glTexCoord2f(1, 0); glVertex2f(150, 80);
			glTexCoord2f(0, 0); glVertex2f(0, 80);
		}
		glEnd();
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

//-------------------------------------

//-------------------------------------
//�_�b�V���Q�[�W�̃C���^�[�t�F�C�X

void Character::printDashGauge(){

	//�C���^�[�t�F�C�X����

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//�A�C�R������
		glPushMatrix();
		{
			glTranslatef(5, 255, 0);

			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("DashIcon"));

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

			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("DashGauge"));

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
				if (DASH_GAUGE_MAX == m_dashPower) {
					glColor3f(1, rand() % 256 / 255.f, rand() % 256 / 255.f);
				}
				else {
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
	glPopAttrib();

}

//-------------------------------------

//�v���C���[�X�e�[�^�X�̕\��

void Character::printStatus()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_DEPTH_TEST);

		if (false == m_isGoal)
		{

			//�_�b�V���Q�[�W�̕`��
			printDashGauge();

			float scale = 0.1f;
			oka::Vec3 color = oka::Vec3(1.0f, 0.0f, 0.0f);
			float width = 2.0f;

			oka::DrawString("LAP", glm::vec2(230.0f, 250.0f), scale, color, width);
			oka::DrawString("/", glm::vec2(275.0f, 250.0f), scale, color, width);
			oka::DrawString(RaceManager::GetInstance()->m_rapMax, glm::vec2(285.0f, 250.0f), scale, color, width);

			scale = 0.13f;
			oka::DrawString("TIME", glm::vec2(180.0f, 280.0f), scale, color, width);
			oka::DrawString(m_totalTime, glm::vec2(220.0f, 280.0f), scale, color, width);

			scale = 0.18f;
			oka::DrawString(m_lap, glm::vec2(260.0f, 250.0f), scale, color, width);

			scale = 0.08;
			oka::DrawString("LAP1", glm::vec2(220.0f, 230.0f), scale, color, width);
			oka::DrawString(m_lapTime[FIRST], glm::vec2(250.0f, 230.0f), scale, color, width);

			oka::DrawString("LAP2", glm::vec2(220.0f, 215.0f), scale, color, width);
			oka::DrawString(m_lapTime[SECOND], glm::vec2(250.0f, 215.0f), scale, color, width);

			oka::DrawString("LAP3", glm::vec2(220.0f, 200.0f), scale, color, width);
			oka::DrawString(m_lapTime[THIRD], glm::vec2(250.0f, 200.0f), scale, color, width);



		}
		else
		{
			printGoal();

			/*glColor3f(1, 0, 0);
			oka::DrawString("LAP1", 60.0f, 160.0f, 0.2f);
			oka::DrawString(m_lapTime[FIRST], 130.0f, 155.0f, 0.2f);

			oka::DrawString("LAP2", 60.0f, 115.0f, 0.2f);
			oka::DrawString(m_lapTime[SECOND], 130.0f, 115.0f, 0.2f);

			oka::DrawString("LAP3", 60.0f, 75.0f, 0.2f);
			oka::DrawString(m_lapTime[THIRD], 130.0f, 75.0f, 0.2f);

			oka::DrawString("TOTALTIME", 25.0f, 30.0f, 0.15f);
			oka::DrawString(m_totalTime, 130.0f, 30.0f, 0.2f);*/



			if (RaceManager::GetInstance()->IsRaceEnd())
			{
				//if ((oka::GameManager::GetInstance()->m_flame % 60) < 30)
				//{
				//	//oka::DrawString("PushStartButton!!", 220.0f, 10.0f, 0.08f);			
				//}
			}

		}
	}
}


//---------------------------------------------------------------
//�v���C���[���R�[�X����������1���������ǂ����̔�����s��
//�S�[���̈ʒu�ɂ���Ƃ��Ƀ`�F�b�N�|�C���g��ʉ߂��Ă��邩���ʂ���
//�t���O��true�̏�Ԃ̂Ƃ��̂�true��Ԃ�1���ƃJ�E���g����

bool Character::countLap()
{

	if (RaceManager::GetInstance()->m_course->m_buffer[COURSE_HEIGHT - 1 + (int)m_transform.GetPosition().m_z][(int)m_transform.GetPosition().m_x] == GOAL)
	{
		bool fg = true;

		for (int i = 0; i < Course::checkPointNum; i++)
		{
			fg &= m_passCheckPoint[i];

		}

		if (fg)
		{
			return true;

		}
	}

	return false;

}

//-------------------------------------
//�v���C���[���S�[���������̔���
//���񐔂�����̎��񐔂ɂȂ������_��true��Ԃ��S�[���Ƃ���

bool Character::checkIsGoal()
{
	if (3 == m_lapCount)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//�v���C���[�������Ă���A�C�e���̌���Ԃ�

int Character::hasItemNumber()
{
	return m_hasItem.size();
}

//-------------------------------------
//�v���C���[���A�C�e���������Ă���Ƃ��̂�
//�����Ă���A�C�e���̃��X�g�̎�ނ�Ԃ�

int Character::hasItemLast()
{

	int itemLast = m_hasItem.size() - 1;

	return m_hasItem[itemLast];

}