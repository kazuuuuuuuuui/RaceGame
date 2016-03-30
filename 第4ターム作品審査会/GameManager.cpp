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
	//シングルトンにするためインスタンスがない場合のみnewし
	//既にインスタンスがある場合はそのインスタンスをそのまま返す

	GameManager* GameManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new GameManager();
		}
		return m_instance;
	}

	//--------------------------------------
	//ゲームのマネージャー更新
	//常にオブジェクトの活性状態を判別する

	void GameManager::Updata()
	{
		CheckGameObject();//関数名変えたい

		//_sequence.Run(this, 1.0f / 60.0f);

	}

	//-------------------------------------
	//ゲームに現れるオブジェクトの追加
	//管理しているベクターに追加する

	void GameManager::AddGameObject(GameObject *_object)
	{
		m_gameObject.push_back(_object);
	}


	//--------------------------------------------
	//ゲームに現れるオブジェクトのメモリ解放と削除
	//非活性ならばメモリを解放しベクターから除外する

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
























	//接触判定
	//取り敢えず
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
	//タイトル処理
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
//			printf("タイトルシーンが初期化されました\n");
//			printf("\n");
//
//			//最初の順位設定と順位付与
//			RaceManager::GetInstance()->CheckRanking(CharacterManager::GetInstance()->m_character);
//
//
//			oka::SoundManager::GetInstance()->Play("TitleBGM");
//
//		}
//
//		glViewport(0, 0, oka::ScreenManager::GetInstance()->GetWidth(), oka::ScreenManager::GetInstance()->GetHeight());
//
//		//更新
//		g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);
//
//		//描画
//		glClear(GL_COLOR_BUFFER_BIT);
//		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//
//		//文字描画変えたい
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
//		//シーンの遷移
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
//	//コース選択処理
//
//	void GameManager::sceneCourseSelect(float delta)
//	{
//		if (0.0f == _sequence.GetTime())
//		{
//			printf("コースセレクトシーンが初期化されました\n");
//			printf("\n");
//
//			//アイテムの添え字初期化
//			itemNum = 0;
//
//		}
//
//		//ビューポートの設定
//		const int x = 0;
//		const int y = 0;
//		const int width = oka::ScreenManager::GetInstance()->GetWidth();
//		const int height = oka::ScreenManager::GetInstance()->GetHeight();
//
//		oka::ScreenManager::GetInstance()->SetViewport(x, y, width, height);
//
//		//更新
//		g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);
//
//		//描画
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
//			//アイテム生成→コースの生成→アイテムの設置
//
//			//アイテムの生成
//			for (unsigned int i = 0; i < ItemManager::GetInstance()->m_item.size(); i++)
//			{
//				oka::GameManager::GetInstance()->AddGameObject(ItemManager::GetInstance()->m_item[i]);
//			}
//
//			//コースの生成
//			RaceManager::GetInstance()->m_course = createCourse();
//
//			oka::GameManager::GetInstance()->AddGameObject(RaceManager::GetInstance()->m_course);
//
//
//			//プレイヤーの初期座標決定
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
//		//プレイシーンに移行
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
//		//深度テスト
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
//		//煙の描画
//		/*for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++)
//		{
//			CharacterManager::GetInstance()->m_character[i]->m_smoke.Draw();
//		}*/
//
//
//		/*更新*/
//		g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);
//
//		RaceManager::GetInstance()->CountRaceStart();
//		RaceManager::GetInstance()->PrintRaceStrart();
//
//		/*描画(2D)*/
//
//		//順位の表示
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
//			printf("プレイシーンが初期化されました\n");
//			printf("\n");
//
//			//プレイヤーのエンジン音
//			oka::Sound::Play(CharacterManager::GetInstance()->m_character[0]->m_engine);
//		}
//
//
//
//		/********************************
//
//		更新部分
//
//		*********************************/
//
//		//レースが始まったらする処理
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
//			//全オブジェクトのUpdate
//			for (unsigned int i = 0; i < oka::GameManager::GetInstance()->m_gameObject.size(); i++)
//			{
//				oka::GameManager::GetInstance()->m_gameObject[i]->Update();
//			}
//
//			//接触判定
//			//for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++)
//			//{
//			//	for (unsigned int t = i + 1; t < CharacterManager::GetInstance()->GetCharacterNumber(); t++) 
//				//{
//			//		//前輪と前輪
//			//		if (isHitCharacter(CharacterManager::GetInstance()->m_character[i]->m_frontPosition, CharacterManager::GetInstance()->m_character[t]->m_frontPosition) ||
//
//			//			//前輪と後輪
//			//			isHitCharacter(CharacterManager::GetInstance()->m_character[i]->m_frontPosition, CharacterManager::GetInstance()->m_character[t]->m_backPosition) ||
//
//			//			//後輪と前輪
//			//			isHitCharacter(CharacterManager::GetInstance()->m_character[i]->m_backPosition, CharacterManager::GetInstance()->m_character[t]->m_frontPosition) ||
//
//			//			//後輪と後輪
//			//			isHitCharacter(CharacterManager::GetInstance()->m_character[i]->m_frontPosition, CharacterManager::GetInstance()->m_character[t]->m_frontPosition)) {
//
//			//			//1フレーム前の座標に戻して進行方向とは
//			//			//逆のベクトルを足し込む
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
//		//描画(3D)
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
//		//	////左上
//		//	//glViewport(0, g_window_height / 2, g_window_width / 2, g_window_height / 2);
//		//	//g_camera->SetPosition({
//		//	//	player1->transform.m_position.m_x + sin(player1->transform.m_rotate.m_y) * 8,
//		//	//	player1->transform.m_position.m_y + 3.5f,
//		//	//	player1->transform.m_position.m_z + cos(player1->transform.m_rotate.m_y) * 8
//		//	//});
//		//	//g_camera->SetTarget({ player1->transform.m_position });
//		//	//g_camera->update(TYPE_3D);
//		//	//Render(player1);
//		//	////右上
//		//	//glViewport(g_window_width / 2, g_window_height / 2, g_window_width / 2, g_window_height / 2);
//		//	//g_camera->SetPosition({
//		//	//	player2->transform.m_position.m_x + sin(player2->transform.m_rotate.m_y) * 8,
//		//	//	player2->transform.m_position.m_y + 3.5f,
//		//	//	player2->transform.m_position.m_z + cos(player2->transform.m_rotate.m_y) * 8
//		//	//});
//		//	//g_camera->SetTarget({ player2->transform.m_position });
//		//	//g_camera->update(TYPE_3D);
//		//	//Render(player2);
//		//	////左下
//		//	//glViewport(0, 0, g_window_width / 2, g_window_height / 2);
//		//	//g_camera->SetPosition({
//		//	//	player3->transform.m_position.m_x + sin(player3->transform.m_rotate.m_y) * 8,
//		//	//	player3->transform.m_position.m_y + 3.5f,
//		//	//	player3->transform.m_position.m_z + cos(player3->transform.m_rotate.m_y) * 8
//		//	//});
//		//	//g_camera->SetTarget({ player3->transform.m_position });
//		//	//g_camera->update(TYPE_3D);
//		//	//Render(player3);
//		//	////右下
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
//		//	//スタートボタンが押されたら
//		//	//タイトルシーンに移行
//		//	if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_START)
//		//	{
//		//		GameManager::GetInstance()->_sequence.change(&GameManager::sceneTitle);
//
//		//		title_pushAnyKey = false;
//		//		modeCommand = SINGLE_MODE;
//
//		//		//コースbgm停止
//		//		//course->m_bgm->stop();
//
//		//		//エンジン音を止める
//		//		//player1->m_engine->stop();
//
//		//		//ループに必要な初期化処理
//		//		//startRace = false;
//		//		//startFrame = 0;//フレーム数
//		//		//timenow = 0;//経過時間
//		//		//timebase = 0;//計測開始時間
//		//		//startCount = 6;
//
//		//		//周回数表示クリア
//		//		//memset(str_lapMax, 0, sizeof(str_lapMax));
//
//		//		//キャラクター削除
//		//		/*for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++) {
//
//		//			delete character[i];
//
//		//		}
//		//		character.clear();*/
//
//		//		//エフェクト削除
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