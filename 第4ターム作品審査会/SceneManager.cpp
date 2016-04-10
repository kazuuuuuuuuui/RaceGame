#include<stdio.h>
#include"SceneManager.h"
#include"RaceManager.h"
#include"JoysticManager.h"
#include"CharacterManager.h"
#include"SoundManager.h"

#include"CourseSelectScene.h"
#include"GameMainScene.h"
#include"PauseScene.h"

namespace oka
{
	SceneManager* SceneManager::m_instance = nullptr;

	//-------------------------------------
	//�R���X�g���N�^

	SceneManager::SceneManager()
	{
		m_nowScene = new TitleScene();
		m_prevScene = new TitleScene();
		m_sequence.Change(&SceneManager::Title);
	}


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
			delete m_prevScene;
			m_prevScene = m_nowScene;
			m_nowScene = new TitleScene();

			printf("�^�C�g���V�[��������������܂���\n");
			printf("\n");

			//�ύX�\��
			//�ŏ��̏��ʐݒ�Ə��ʕt�^
			RaceManager::GetInstance()->CheckRanking(CharacterManager::GetInstance()->m_character);

			oka::SoundManager::GetInstance()->Play("TitleBGM");

		}

		m_nowScene->Update();
		m_nowScene->Render();

		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
		{
			if (TitleScene::GameMode::exit == TitleScene::m_gameMode)
			{
				exit(EXIT_SUCCESS);
			}
			else
			{
				printf("�R�[�X�I���V�[���Ɉڂ�܂�\n");

				m_sequence.Change(&SceneManager::CourseSelect);
				oka::SoundManager::GetInstance()->Play("modeDecision");
			}
		}

	}

	//-------------------------------------
	//�R�[�X�I���V�[��

	void SceneManager::CourseSelect(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			delete m_prevScene;
			m_prevScene = m_nowScene;
			m_nowScene = new CourseSelectScene();

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
			m_sequence.Change(&SceneManager::GameMain);
		}
		else if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_B)
		{
			printf("�^�C�g���V�[���ɖ߂�܂�\n");
			m_sequence.Change(&SceneManager::Title);
		}
	}


	//-------------------------------------
	//�Q�[���V�[��

	void SceneManager::GameMain(float delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			m_prevScene = m_nowScene;
			m_nowScene = new GameMainScene();

			printf("�v���C�V�[��������������܂���\n");
			printf("\n");

		}

		m_nowScene->Update();
		m_nowScene->Render();

		//�|�[�Y�V�[���Ɉڍs
		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_START)
		{
			printf("�|�[�Y�V�[���Ɉڂ�܂�\n");
			m_sequence.Change(&SceneManager::Pause);
		}
	}

	//-------------------------------------
	//�Q�[�����̃|�[�Y�V�[��
	void SceneManager::Pause(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			m_prevScene = m_nowScene;
			m_nowScene = new PauseScene();

			printf("�|�[�Y�V�[��������������܂���\n");
			printf("\n");

		}

		m_prevScene->Render();

		m_nowScene->Update();
		m_nowScene->Render();

		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
		{
			if (PauseScene::Mode::backGame == PauseScene::m_mode)
			{
				printf("�Q�[���V�[���ɖ߂�܂�\n");
				m_sequence.Change(&SceneManager::GameMain);
			}
			else if (PauseScene::Mode::backTitle == PauseScene::m_mode)
			{
				printf("�^�C�g���V�[���ɖ߂�܂�\n");
				m_sequence.Change(&SceneManager::Title);
			}
			else if(PauseScene::Mode::backCourseSelect == PauseScene::m_mode)
			{
				printf("�R�[�X�I���V�[���ɖ߂�܂�\n");
				m_sequence.Change(&SceneManager::CourseSelect);

			}
			else if(PauseScene::Mode::exit == PauseScene::m_mode)
			{
				exit(EXIT_SUCCESS);
			}
		}

	}


}//namespace oka