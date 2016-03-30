#include<stdio.h>
#include<stdlib.h>
#include<vector>
#define _USE_MATH_DEFINES
#include<math.h>
#include<time.h>
#include<list>
#include"GameManager.h"
#include"camera.h"
#include"Course.h"
#include"CourseFlag.h"
#include"Item.h"
#include"Effect.h"
#include"Fire.h"
#include"Blizzard.h"
#include"StrokeString.h"
#include"Smoke.h"
#include"Vec3.h"
#include"Texture.h"
#include"CharacterManager.h"
#include"TimeManager.h"
#include"ItemManager.h"
#include"JoysticManager.h"
#include"ImageManager.h"
#include"SoundManager.h"
#include"ScreenManager.h"
#include"RaceManager.h"
#include"Sound.h"
#include"glut.h"

namespace oka
{
	GameManager* GameManager::m_instance = nullptr;

	//------------------------------------------------------------
	//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
	//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�

	GameManager* GameManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new GameManager();
		}
		return m_instance;
	}

	//--------------------------------------
	//�Q�[���̃}�l�[�W���[�X�V
	//��ɃI�u�W�F�N�g�̊�����Ԃ𔻕ʂ���

	void GameManager::Updata()
	{
		CheckGameObject();//�֐����ς�����

		//_sequence.Run(this, 1.0f / 60.0f);

	}

	//-------------------------------------
	//�Q�[���Ɍ����I�u�W�F�N�g�̒ǉ�
	//�Ǘ����Ă���x�N�^�[�ɒǉ�����

	void GameManager::AddGameObject(GameObject *_object)
	{
		m_gameObject.push_back(_object);
	}


	//--------------------------------------------
	//�Q�[���Ɍ����I�u�W�F�N�g�̃���������ƍ폜
	//�񊈐��Ȃ�΃�������������x�N�^�[���珜�O����

	void GameManager::CheckGameObject()
	{
		auto itr = m_gameObject.begin();
		while (itr != m_gameObject.end())
		{
			if ((*itr)->CheckIsActive())
			{

			}
			else
			{
				delete (*itr);
				itr = m_gameObject.erase(itr);
				continue;
			}

			itr++;

		}
	}
























	//�ڐG����
	//��芸����
	bool isHitCharacter(oka::Vec3 _myPos, oka::Vec3 _youPos)
	{
		oka::Vec3 v = _myPos - _youPos;

		float hitLine = 2.4f;

		if (v.length() < hitLine) {
			return true;
		}

		return false;

	}





	//-------------------------------------------------------------------------------------------------------
	//�^�C�g������
//	enum
//	{
//		SINGLE_MODE = 0,
//		VS_MODE,
//		TITLE_MAX
//	};
//
//	bool title_pushAnyKey = false;
//	int modeCommand = SINGLE_MODE;
//
//	void GameManager::sceneTitle(float delta)
//	{
//
//		if (0.0f == _sequence.GetTime())
//		{
//			printf("�^�C�g���V�[��������������܂���\n");
//			printf("\n");
//
//			//�ŏ��̏��ʐݒ�Ə��ʕt�^
//			RaceManager::GetInstance()->CheckRanking(CharacterManager::GetInstance()->m_character);
//
//
//			oka::SoundManager::GetInstance()->Play("TitleBGM");
//
//		}
//
//		glViewport(0, 0, oka::ScreenManager::GetInstance()->GetWidth(), oka::ScreenManager::GetInstance()->GetHeight());
//
//		//�X�V
//		g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);
//
//		//�`��
//		glClear(GL_COLOR_BUFFER_BIT);
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//		//�����`��ς�����
//		glm::vec2 position = glm::vec2(70.0f, 180.0f);
//		float scale = 0.3f;
//		oka::Vec3 color = oka::Vec3(1.0f, 1.0f, 1.0f);
//		float width = 5.0f;
//
//		oka::DrawString("Bike", position, scale, color,width);
//
//		position = glm::vec2(110.0f, 135.0f);
//		scale = 0.3f;
//		color = oka::Vec3(1.0f, 1.0f, 1.0f);
//		width = 5.0f;
//
//		oka::DrawString("Racing", position, scale, color, width);
//
//		//�V�[���̑J��
//		if ((false == title_pushAnyKey) && (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_START))
//		{
//			title_pushAnyKey = true;
//			oka::SoundManager::GetInstance()->Play("pushStartButtonSE");
//
//		}
//
//		if (false == title_pushAnyKey)
//		{
//
//			if ((oka::TimeManager::GetInstance()->m_flame % 60) < 30)
//			{
//				glm::vec2 position = glm::vec2(85.0f, 40.0f);
//				float scale = 0.1f;
//				oka::Vec3 color = oka::Vec3(1.0f, 1.0f, 1.0f);
//				float width = 1.5f;
//
//				oka::DrawString("Push Start Button", position, scale, color, width);
//			}
//
//		}
//		else
//		{
//			if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_yTopDown)
//			{
//				modeCommand++;
//				modeCommand = (modeCommand + TITLE_MAX) % TITLE_MAX;
//				oka::SoundManager::GetInstance()->Play("cursorMoveSE");
//
//			}
//
//			if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_yBottomDown)
//			{
//				modeCommand--;
//				modeCommand = (modeCommand + TITLE_MAX) % TITLE_MAX;
//				oka::SoundManager::GetInstance()->Play("cursorMoveSE");
//
//			}
//
//
//			if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
//			{
//				GameManager::GetInstance()->_sequence.Change(&GameManager::sceneCourseSelect);
//				oka::SoundManager::GetInstance()->Play("modeDecision");
//			}
//
//			oka::SetLineWidth(4.0f);
//			if (SINGLE_MODE == modeCommand)
//			{
//				glm::vec2 position = glm::vec2(100.0f, 55.0f);
//				float scale = 0.1f;
//				oka::Vec3 color = oka::Vec3(1.0f, 0.0f, 0.0f);
//				float width = 1.0f;
//
//				oka::DrawString("Single Mode", position, scale, color, width);
//			}
//			else
//			{
//				glm::vec2 position = glm::vec2(100.0f, 55.0f);
//				float scale = 0.1f;
//				oka::Vec3 color = oka::Vec3(1.0f, 1.0f, 1.0f);
//				float width = 1.0f;
//
//				oka::DrawString("Single Mode", position, scale, color, width);
//			}
//
//			if (VS_MODE == modeCommand)
//			{
//				glm::vec2 position = glm::vec2(115.0f, 25.0f);
//				float scale = 0.1f;
//				oka::Vec3 color = oka::Vec3(1.0f, 0.0f, 0.0f);
//				float width = 1.0f;
//
//				oka::DrawString("Vs Mode", position, scale, color, width);
//			}
//			else
//			{
//				glm::vec2 position = glm::vec2(115.0f, 25.0f);
//				float scale = 0.1f;
//				oka::Vec3 color = oka::Vec3(1.0f, 1.0f, 1.0f);
//				float width = 1.0f;
//
//				oka::DrawString("Vs Mode", position, scale, color, width);
//			}
//		}
//
//	}
//
//	//-------------------------------------------------------------------------------------------------------
//	//�R�[�X�I������
//
//	void GameManager::sceneCourseSelect(float delta)
//	{
//		if (0.0f == _sequence.GetTime())
//		{
//			printf("�R�[�X�Z���N�g�V�[��������������܂���\n");
//			printf("\n");
//
//			//�A�C�e���̓Y����������
//			itemNum = 0;
//
//		}
//
//		//�r���[�|�[�g�̐ݒ�
//		const int x = 0;
//		const int y = 0;
//		const int width = oka::ScreenManager::GetInstance()->GetWidth();
//		const int height = oka::ScreenManager::GetInstance()->GetHeight();
//
//		oka::ScreenManager::GetInstance()->SetViewport(x, y, width, height);
//
//		//�X�V
//		g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);
//
//		//�`��
//		glClear(GL_COLOR_BUFFER_BIT);
//		glClearColor(0.f, 0.f, 0.f, 1.f);
//
//		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_xRightDown) {
//
//			selectedCourse++;
//			selectedCourse = (selectedCourse + COURSE_NUM_MAX) % COURSE_NUM_MAX;
//			oka::SoundManager::GetInstance()->Play("cursorMoveSE");
//
//		}
//
//		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_xLeftDown) {
//
//			selectedCourse--;
//			selectedCourse = (selectedCourse + COURSE_NUM_MAX) % COURSE_NUM_MAX;
//			oka::SoundManager::GetInstance()->Play("cursorMoveSE");
//
//		}
//
//		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
//		{
//			oka::SoundManager::GetInstance()->Stop("TitleBGM");
//			oka::SoundManager::GetInstance()->Play("courseDecision");
//
//
//			//�A�C�e���������R�[�X�̐������A�C�e���̐ݒu
//
//			//�A�C�e���̐���
//			for (unsigned int i = 0; i < ItemManager::GetInstance()->m_item.size(); i++)
//			{
//				oka::GameManager::GetInstance()->AddGameObject(ItemManager::GetInstance()->m_item[i]);
//			}
//
//			//�R�[�X�̐���
//			RaceManager::GetInstance()->m_course = createCourse();
//
//			oka::GameManager::GetInstance()->AddGameObject(RaceManager::GetInstance()->m_course);
//
//
//			//�v���C���[�̏������W����
//			if (COURSE1 == selectedCourse)
//			{
//				RaceManager::GetInstance()->m_bgm = oka::Sound::LoadWavFile("wav/course1BGM.wav");
//
//				CharacterManager::GetInstance()->m_character[0]->m_transform.SetPosition(oka::Vec3(14.f, 0.0f, -165.f));
//				CharacterManager::GetInstance()->m_character[1]->m_transform.SetPosition(oka::Vec3(18.f, 0.f, -160.f));
//				CharacterManager::GetInstance()->m_character[2]->m_transform.SetPosition(oka::Vec3(22.f, 0.f, -155.f));
//				CharacterManager::GetInstance()->m_character[3]->m_transform.SetPosition(oka::Vec3(26.f, 0.f, -150.f));
//
//			}
//
//			else if (COURSE2 == selectedCourse)
//			{
//				RaceManager::GetInstance()->m_bgm = oka::Sound::LoadWavFile("wav/course2BGM.wav");
//
//				CharacterManager::GetInstance()->m_character[0]->m_transform.SetPosition(oka::Vec3(17.f, 0.f, -110.5f));
//				CharacterManager::GetInstance()->m_character[1]->m_transform.SetPosition(oka::Vec3(25.f, 0.f, -105.5f));
//				CharacterManager::GetInstance()->m_character[2]->m_transform.SetPosition(oka::Vec3(33.f, 0.f, -100.5f));
//				CharacterManager::GetInstance()->m_character[3]->m_transform.SetPosition(oka::Vec3(41.f, 0.f, -95.5f));
//
//			}
//
//		}
//
//		//�v���C�V�[���Ɉڍs
//		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
//		{
//			GameManager::GetInstance()->_sequence.Change(&GameManager::scenePlay);
//		}
//
//		glFlush();
//
//	}
//
//
//
//	//
//	void Render(Character *_pCharacter)
//	{
//		//�[�x�e�X�g
//		glEnable(GL_DEPTH_TEST);
//
//		for (unsigned int i = 0; i < GameManager::GetInstance()->m_gameObject.size(); i++)
//		{
//			GameManager::GetInstance()->m_gameObject[i]->Draw();
//		}
//
//		for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++)
//		{
//			CharacterManager::GetInstance()->m_character[i]->drawHasItem();
//		}
//
//		glDisable(GL_DEPTH_TEST);
//
//		//���̕`��
//		/*for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++)
//		{
//			CharacterManager::GetInstance()->m_character[i]->m_smoke.Draw();
//		}*/
//
//
//		/*�X�V*/
//		g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);
//
//		RaceManager::GetInstance()->CountRaceStart();
//		RaceManager::GetInstance()->PrintRaceStrart();
//
//		/*�`��(2D)*/
//
//		//���ʂ̕\��
//		_pCharacter->printRanking();
//		_pCharacter->printStatus();
//
//
//	}
//
//	//-------------------------------------------------------------------------------------------------------
//	void GameManager::scenePlay(float delta)
//	{
//		if (0.0f == _sequence.GetTime())
//		{
//			printf("�v���C�V�[��������������܂���\n");
//			printf("\n");
//
//			//�v���C���[�̃G���W����
//			oka::Sound::Play(CharacterManager::GetInstance()->m_character[0]->m_engine);
//		}
//
//
//
//		/********************************
//
//		�X�V����
//
//		*********************************/
//
//		//���[�X���n�܂����炷�鏈��
//		if (RaceManager::GetInstance()->m_raceStart)
//		{
//			RaceManager::GetInstance()->CheckRanking(CharacterManager::GetInstance()->m_character);
//
//			for (unsigned int i = 0; i < oka::JoysticManager::GetInstance()->GetContorollerNumber(); i++)
//			{
//				if (oka::JoysticManager::GetInstance()->GetContoroller(i).m_isConnect)
//				{
//					unsigned short pressedKey = oka::JoysticManager::GetInstance()->GetContoroller(i).m_state.Gamepad.wButtons;
//					unsigned int downKeys = oka::JoysticManager::GetInstance()->GetContoroller(i).m_downkey;
//					float sThumbLX = oka::JoysticManager::GetInstance()->GetContoroller(i).m_sThumbLX;
//					float sThumbLY = oka::JoysticManager::GetInstance()->GetContoroller(i).m_sThumbLY;
//
//					CharacterManager::GetInstance()->m_character[i]->control(pressedKey, downKeys, sThumbLX, sThumbLY);
//				}
//				else
//				{
//					//CharacterManager::GetInstance()->m_character[i]->control();
//				}
//
//			}
//
//			//�S�I�u�W�F�N�g��Update
//			for (unsigned int i = 0; i < oka::GameManager::GetInstance()->m_gameObject.size(); i++)
//			{
//				oka::GameManager::GetInstance()->m_gameObject[i]->Update();
//			}
//
//			//�ڐG����
//			//for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++)
//			//{
//			//	for (unsigned int t = i + 1; t < CharacterManager::GetInstance()->GetCharacterNumber(); t++) 
//				//{
//			//		//�O�ւƑO��
//			//		if (isHitCharacter(CharacterManager::GetInstance()->m_character[i]->m_frontPosition, CharacterManager::GetInstance()->m_character[t]->m_frontPosition) ||
//
//			//			//�O�ւƌ��
//			//			isHitCharacter(CharacterManager::GetInstance()->m_character[i]->m_frontPosition, CharacterManager::GetInstance()->m_character[t]->m_backPosition) ||
//
//			//			//��ւƑO��
//			//			isHitCharacter(CharacterManager::GetInstance()->m_character[i]->m_backPosition, CharacterManager::GetInstance()->m_character[t]->m_frontPosition) ||
//
//			//			//��ւƌ��
//			//			isHitCharacter(CharacterManager::GetInstance()->m_character[i]->m_frontPosition, CharacterManager::GetInstance()->m_character[t]->m_frontPosition)) {
//
//			//			//1�t���[���O�̍��W�ɖ߂��Đi�s�����Ƃ�
//			//			//�t�̃x�N�g���𑫂�����
//			//			oka::Vec3 reverse = CharacterManager::GetInstance()->m_character[i]->m_transform.GetPosition() - CharacterManager::GetInstance()->m_character[t]->m_transform.GetPosition();
//			//			CharacterManager::GetInstance()->m_character[i]->m_speed += reverse*0.01f;
//			//			CharacterManager::GetInstance()->m_character[t]->m_speed -= reverse*0.01f;
//			//		}
//			//	}
//			//}
//
//		}
//
//		//-------------------------------------
//		//�`��(3D)
//
//		if (SINGLE_MODE == modeCommand)
//		{
//
//			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//			const oka::Vec3 color = RaceManager::GetInstance()->m_course->m_backgroundColor;
//			glClearColor(color.m_x, color.m_y, color.m_z, 1);
//
//			oka::Vec3 position;
//			position.m_x = CharacterManager::GetInstance()->m_character[0]->m_transform.GetPosition().m_x + sin(CharacterManager::GetInstance()->m_character[0]->m_transform.GetRotation().m_y) * 8;
//			position.m_y = CharacterManager::GetInstance()->m_character[0]->m_transform.GetPosition().m_y + 3.5f;
//			position.m_z = CharacterManager::GetInstance()->m_character[0]->m_transform.GetPosition().m_z + cos(CharacterManager::GetInstance()->m_character[0]->m_transform.GetRotation().m_y) * 8;
//
//			oka::Vec3 target;
//			target = CharacterManager::GetInstance()->m_character[0]->m_transform.GetPosition();
//
//			oka::Vec3 up = oka::Vec3(0, 1, 0);
//
//			g_camera->Perspective();
//			g_camera->SetViewMatrix(position, target, up);
//			g_camera->MultViewMatrix();
//
//			Render(CharacterManager::GetInstance()->m_character[0]);
//
//		}
//
//		//else if (VS_MODE == modeCommand)
//		//{
//		//	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		//	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//		//	//glClearColor(77.f / 255.f, 180.f / 255.f, 232.f / 255.f, 1);
//		//	////����
//		//	//glViewport(0, g_window_height / 2, g_window_width / 2, g_window_height / 2);
//		//	//g_camera->SetPosition({
//		//	//	player1->transform.m_position.m_x + sin(player1->transform.m_rotate.m_y) * 8,
//		//	//	player1->transform.m_position.m_y + 3.5f,
//		//	//	player1->transform.m_position.m_z + cos(player1->transform.m_rotate.m_y) * 8
//		//	//});
//		//	//g_camera->SetTarget({ player1->transform.m_position });
//		//	//g_camera->update(TYPE_3D);
//		//	//Render(player1);
//		//	////�E��
//		//	//glViewport(g_window_width / 2, g_window_height / 2, g_window_width / 2, g_window_height / 2);
//		//	//g_camera->SetPosition({
//		//	//	player2->transform.m_position.m_x + sin(player2->transform.m_rotate.m_y) * 8,
//		//	//	player2->transform.m_position.m_y + 3.5f,
//		//	//	player2->transform.m_position.m_z + cos(player2->transform.m_rotate.m_y) * 8
//		//	//});
//		//	//g_camera->SetTarget({ player2->transform.m_position });
//		//	//g_camera->update(TYPE_3D);
//		//	//Render(player2);
//		//	////����
//		//	//glViewport(0, 0, g_window_width / 2, g_window_height / 2);
//		//	//g_camera->SetPosition({
//		//	//	player3->transform.m_position.m_x + sin(player3->transform.m_rotate.m_y) * 8,
//		//	//	player3->transform.m_position.m_y + 3.5f,
//		//	//	player3->transform.m_position.m_z + cos(player3->transform.m_rotate.m_y) * 8
//		//	//});
//		//	//g_camera->SetTarget({ player3->transform.m_position });
//		//	//g_camera->update(TYPE_3D);
//		//	//Render(player3);
//		//	////�E��
//		//	//glViewport(g_window_width / 2, 0, g_window_width / 2, g_window_height / 2);
//		//	//g_camera->SetPosition({
//		//	//	player4->transform.m_position.m_x + sin(player4->transform.m_rotate.m_y) * 8,
//		//	//	player4->transform.m_position.m_y + 3.5f,
//		//	//	player4->transform.m_position.m_z + cos(player4->transform.m_rotate.m_y) * 8
//		//	//});
//		//	//g_camera->SetTarget({ player4->transform.m_position });
//		//	//g_camera->update(TYPE_3D);
//		//	//Render(player4);
//		//}
//
//		//if (RaceManager::GetInstance()->IsRaceEnd())
//		//{
//		//	//�X�^�[�g�{�^���������ꂽ��
//		//	//�^�C�g���V�[���Ɉڍs
//		//	if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_START)
//		//	{
//		//		GameManager::GetInstance()->_sequence.change(&GameManager::sceneTitle);
//
//		//		title_pushAnyKey = false;
//		//		modeCommand = SINGLE_MODE;
//
//		//		//�R�[�Xbgm��~
//		//		//course->m_bgm->stop();
//
//		//		//�G���W�������~�߂�
//		//		//player1->m_engine->stop();
//
//		//		//���[�v�ɕK�v�ȏ���������
//		//		//startRace = false;
//		//		//startFrame = 0;//�t���[����
//		//		//timenow = 0;//�o�ߎ���
//		//		//timebase = 0;//�v���J�n����
//		//		//startCount = 6;
//
//		//		//���񐔕\���N���A
//		//		//memset(str_lapMax, 0, sizeof(str_lapMax));
//
//		//		//�L�����N�^�[�폜
//		//		/*for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++) {
//
//		//			delete character[i];
//
//		//		}
//		//		character.clear();*/
//
//		//		//�G�t�F�N�g�폜
//		//		//effect.clear();
//
//		//	}
//
//		//}
//
//
//		glFlush();
//
//	}
}