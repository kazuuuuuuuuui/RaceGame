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
	//コンストラクタ

	SceneManager::SceneManager()
	{
		m_nowScene = new TitleScene();
		m_prevScene = new TitleScene();
		m_sequence.Change(&SceneManager::Title);
	}


	//------------------------------------------------------------
	//シングルトンにするためインスタンスがない場合のみnewし
	//既にインスタンスがある場合はそのインスタンスをそのまま返す

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
	//タイトルシーン

	void SceneManager::Title(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{	
			delete m_prevScene;
			m_prevScene = m_nowScene;
			m_nowScene = new TitleScene();

			printf("タイトルシーンが初期化されました\n");
			printf("\n");

			//変更予定
			//最初の順位設定と順位付与
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
				printf("コース選択シーンに移ります\n");

				m_sequence.Change(&SceneManager::CourseSelect);
				oka::SoundManager::GetInstance()->Play("modeDecision");
			}
		}

	}

	//-------------------------------------
	//コース選択シーン

	void SceneManager::CourseSelect(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			delete m_prevScene;
			m_prevScene = m_nowScene;
			m_nowScene = new CourseSelectScene();

			printf("コースセレクトシーンが初期化されました\n");
			printf("\n");

			//アイテムの添え字初期化
			itemNum = 0;

		}

		m_nowScene->Update();
		m_nowScene->Render();

		//プレイシーンに移行
		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
		{
			printf("プレイシーンに移ります\n");
			m_sequence.Change(&SceneManager::GameMain);
		}
		else if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_B)
		{
			printf("タイトルシーンに戻ります\n");
			m_sequence.Change(&SceneManager::Title);
		}
	}


	//-------------------------------------
	//ゲームシーン

	void SceneManager::GameMain(float delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			m_prevScene = m_nowScene;
			m_nowScene = new GameMainScene();

			printf("プレイシーンが初期化されました\n");
			printf("\n");

		}

		m_nowScene->Update();
		m_nowScene->Render();

		//ポーズシーンに移行
		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_START)
		{
			printf("ポーズシーンに移ります\n");
			m_sequence.Change(&SceneManager::Pause);
		}
	}

	//-------------------------------------
	//ゲーム中のポーズシーン
	void SceneManager::Pause(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			m_prevScene = m_nowScene;
			m_nowScene = new PauseScene();

			printf("ポーズシーンが初期化されました\n");
			printf("\n");

		}

		m_prevScene->Render();

		m_nowScene->Update();
		m_nowScene->Render();

		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
		{
			if (PauseScene::Mode::backGame == PauseScene::m_mode)
			{
				printf("ゲームシーンに戻ります\n");
				m_sequence.Change(&SceneManager::GameMain);
			}
			else if (PauseScene::Mode::backTitle == PauseScene::m_mode)
			{
				printf("タイトルシーンに戻ります\n");
				m_sequence.Change(&SceneManager::Title);
			}
			else if(PauseScene::Mode::backCourseSelect == PauseScene::m_mode)
			{
				printf("コース選択シーンに戻ります\n");
				m_sequence.Change(&SceneManager::CourseSelect);

			}
			else if(PauseScene::Mode::exit == PauseScene::m_mode)
			{
				exit(EXIT_SUCCESS);
			}
		}

	}


}//namespace oka