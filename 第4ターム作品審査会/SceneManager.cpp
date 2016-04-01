#include<stdio.h>
#include"SceneManager.h"
#include"RaceManager.h"
#include"JoysticManager.h"
#include"CharacterManager.h"
#include"SoundManager.h"

#include"CourseSelectScene.h"
#include"GameMainScene.h"

namespace oka
{
	SceneManager* SceneManager::m_instance = nullptr;

	//------------------------------------------------------------
	//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
	//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�

	SceneManager* SceneManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new SceneManager();
		}
		return m_instance;
	}

	//-------------------------------------

	void SceneManager::Update()
	{
		m_sequence.Run(this, 1.0f / 60.0f);
	}


	//--------------
	//�^�C�g���V�[��

	void SceneManager::Title(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			printf("�^�C�g���V�[��������������܂���\n");
			printf("\n");

			//�ŏ��̏��ʐݒ�Ə��ʕt�^
			RaceManager::GetInstance()->CheckRanking(CharacterManager::GetInstance()->m_character);

			oka::SoundManager::GetInstance()->Play("TitleBGM");

		}

		m_nowScene->Update();
		m_nowScene->Render();

		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
		{
			printf("�R�[�X�I���V�[���Ɉڂ�܂�\n");

			m_prevScene = m_nowScene;
			m_nowScene = new CourseSelectScene();

			m_sequence.Change(&SceneManager::CourseSelect);
			oka::SoundManager::GetInstance()->Play("modeDecision");
		}

	}

	//-------------------------------------
	//�R�[�X�I���V�[��

	void SceneManager::CourseSelect(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			printf("�R�[�X�Z���N�g�V�[��������������܂���\n");
			printf("\n");

			//�A�C�e���̓Y����������
			itemNum = 0;

		}

		m_nowScene->Update();
		m_nowScene->Render();

		//�v���C�V�[���Ɉڍs
		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
		{
			printf("�v���C�V�[���Ɉڂ�܂�\n");

			m_prevScene = m_nowScene;
			m_nowScene = new GameMainScene();

			m_sequence.Change(&SceneManager::GameMain);
		}
	}


	//-------------------------------------
	//�Q�[���V�[��

	void SceneManager::GameMain(float delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			printf("�v���C�V�[��������������܂���\n");
			printf("\n");

			//�v���C���[�̃G���W����
			oka::Sound::Play(CharacterManager::GetInstance()->m_character[0]->m_engine);
		}

		m_nowScene->Update();
		m_nowScene->Render();

	}

}//namespace oka