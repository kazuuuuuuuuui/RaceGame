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
			printf("タイトルシーンが初期化されました\n");
			printf("\n");

			//最初の順位設定と順位付与
			RaceManager::GetInstance()->CheckRanking(CharacterManager::GetInstance()->m_character);

			oka::SoundManager::GetInstance()->Play("TitleBGM");

		}

		m_nowScene->Update();
		m_nowScene->Render();

		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
		{
			printf("コース選択シーンに移ります\n");

			m_prevScene = m_nowScene;
			m_nowScene = new CourseSelectScene();

			m_sequence.Change(&SceneManager::CourseSelect);
			oka::SoundManager::GetInstance()->Play("modeDecision");
		}

	}

	//-------------------------------------
	//コース選択シーン

	void SceneManager::CourseSelect(float _delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
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

			m_prevScene = m_nowScene;
			m_nowScene = new GameMainScene();

			m_sequence.Change(&SceneManager::GameMain);
		}
	}


	//-------------------------------------
	//ゲームシーン

	void SceneManager::GameMain(float delta)
	{
		if (0.0f == m_sequence.GetTime())
		{
			printf("プレイシーンが初期化されました\n");
			printf("\n");

			//プレイヤーのエンジン音
			oka::Sound::Play(CharacterManager::GetInstance()->m_character[0]->m_engine);
		}

		m_nowScene->Update();
		m_nowScene->Render();

	}

}//namespace oka