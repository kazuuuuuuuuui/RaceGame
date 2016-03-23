/*

キャラ格納と順位付けるベクターを分ける必要有り？


*/


#include<stdio.h>
#include<stdlib.h>
#include<vector>
#define _USE_MATH_DEFINES
#include<math.h>
#include<time.h>
#include<algorithm>
#include<list>
#include"GameManager.h"
#include"camera.h"
#include"Course.h"
#include"CourseFlag.h"
#include"Item.h"
#include"Effect.h"
#include"Fire.h"
#include"Blizzard.h"
#include"Dash.h"
#include"StrokeString.h"
#include"Smoke.h"
#include"moji.h"
#include"Vec3.h"
#include"CharacterManager.h"
#include"JoysticManager.h"
#include"ImageManager.h"
#include"SoundManager.h"
#include"RaceManager.h"
#include"Sound.h"
#include"glut.h"

//debug
extern int g_window_width;
extern int g_window_height;



//周回数表示に使う
char str_lapMax[256];

int getMilliSecond(int _flame)
{
	return ((_flame * 1000) / 60) % 1000;
}

int getSecond(int _flame)
{
	return _flame / 60;
}

int getMinute(int _second)
{
	return _second / 60;
}

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


	//-------------------------------------
	//ゲームに現れるオブジェクトの追加
	//管理しているマップに既に登録されている検索し
	//登録されていなければ追加する

	void GameManager::AddGameObject(GameObject *_object)
	{
		m_gameObject.push_back(_object);
	}

	//--------------------------------------
	//

	void GameManager::Updata()
	{
		m_flame++;

		_sequence.run(this, 1.0f / 60.0f);

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

	//順位判定用の関数
	//順位の判定のみする
	bool checkRanking(Character *_character1, Character *_character2)
	{

		//周回数での判定
		if (_character1->m_lapCount > _character2->m_lapCount)
		{
			return true;
		}
		else if (_character1->m_lapCount < _character2->m_lapCount)
		{
			return false;
		}

		//チェックポイントの進み具合での判定
		if (_character1->m_nowPoint > _character2->m_nowPoint)
		{
			return true;
		}
		else if (_character1->m_nowPoint < _character2->m_nowPoint)
		{
			return false;
		}

		//目指しているチェックポイントへの距離での判定
		if (_character1->m_nextCheckPointLength > _character2->m_nextCheckPointLength)
		{
			return false;
		}
		else if (_character1->m_nextCheckPointLength < _character2->m_nextCheckPointLength)
		{
			return true;
		}

		//取り敢えず何か返す
		return false;

	}

	//-------------------------------------
	//ゲームの初期化全般を行う

	void init()
	{
		//コントローラーの対応付け
		for (unsigned int i = 0; i<oka::CharacterManager::GetInstance()->GetCharacterNumber();i++)
		{
			oka::JoysticManager::GetInstance()->AddController(oka::CharacterManager::GetInstance()->m_character[i]->m_contoroller);
		}

printf("%d\n", oka::JoysticManager::GetInstance()->GetConnectingNum());

		//キャラクターの登録
		for (unsigned int i = 0; i<oka::CharacterManager::GetInstance()->GetCharacterNumber(); i++)
		{
			oka::GameManager::GetInstance()->AddGameObject(oka::CharacterManager::GetInstance()->m_character[i]);
		}
	
		
		//カメラの生成
		g_camera = new oka::Camera();

		//テクスチャの読み込み
		oka::ImageManager::GetInstance()->SetHandle("ItemFire", oka::BmpImage::LoadImage3f("bmp/getItem/fire.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("ItemBlizzard", oka::BmpImage::LoadImage3f("bmp/getItem/blizzard.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("CountDown3", oka::BmpImage::LoadImage4f("bmp/start/three.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("CountDown2", oka::BmpImage::LoadImage4f("bmp/start/two.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("CountDown1", oka::BmpImage::LoadImage4f("bmp/start/one.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("Go", oka::BmpImage::LoadImage4f("bmp/start/go.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("Goal", oka::BmpImage::LoadImage4f("bmp/goal.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("Smoke", oka::BmpImage::LoadImage4f("bmp/Effect/smoke.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("Dash", oka::BmpImage::LoadImage4f("bmp/Effect/dash.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("Rank1st", oka::BmpImage::LoadImage4f("bmp/Ranking/1st.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("Rank2nd", oka::BmpImage::LoadImage4f("bmp/Ranking/2nd.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("Rank3rd", oka::BmpImage::LoadImage4f("bmp/Ranking/3rd.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("Rank4th", oka::BmpImage::LoadImage4f("bmp/Ranking/4th.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("DashIcon", oka::BmpImage::LoadImage4f("bmp/dashIcon.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("DashGauge", oka::BmpImage::LoadImage4f("bmp/gauge.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("EffectBlizzard", oka::BmpImage::LoadImage4f("bmp/Effect/blizzard.bmp"));


		//音読み込み	
		oka::SoundManager::GetInstance()->AddSound("pushStartButtonSE", oka::Sound::LoadWavFile("wav/pushStartButton.wav"));
		oka::SoundManager::GetInstance()->AddSound("TitleBGM", oka::Sound::LoadWavFile("wav/titleBGM.wav"));
		oka::SoundManager::GetInstance()->AddSound("cursorMoveSE", oka::Sound::LoadWavFile("wav/cursorMove.wav"));
		oka::SoundManager::GetInstance()->AddSound("modeDecision", oka::Sound::LoadWavFile("wav/modeDecision.wav"));
		oka::SoundManager::GetInstance()->AddSound("courseDecision", oka::Sound::LoadWavFile("wav/courseDecision.wav"));
		oka::SoundManager::GetInstance()->AddSound("slipSE", oka::Sound::LoadWavFile("wav/slip.wav"));
		oka::SoundManager::GetInstance()->AddSound("fireSE", oka::Sound::LoadWavFile("wav/fire.wav"));
		oka::SoundManager::GetInstance()->AddSound("chargeComplete", oka::Sound::LoadWavFile("wav/chargeComplete.wav"));
		oka::SoundManager::GetInstance()->AddSound("getItem", oka::Sound::LoadWavFile("wav/getItem.wav"));
		oka::SoundManager::GetInstance()->AddSound("lapCountSE", oka::Sound::LoadWavFile("wav/lapCount.wav"));
		oka::SoundManager::GetInstance()->AddSound("finalLapSE", oka::Sound::LoadWavFile("wav/finalLap.wav"));
		oka::SoundManager::GetInstance()->AddSound("goalSE", oka::Sound::LoadWavFile("wav/goal.wav"));
		oka::SoundManager::GetInstance()->AddSound("CountDown", oka::Sound::LoadSquareWave(count_sound, sizeof(count_sound), 440));


		//最初の順位設定と順位付与
		for (unsigned int i = 0; i < oka::CharacterManager::GetInstance()->GetCharacterNumber(); i++) 
		{
			std::sort(oka::CharacterManager::GetInstance()->m_character.begin(), oka::CharacterManager::GetInstance()->m_character.end(), checkRanking);
		}

		for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++)
		{
			oka::CharacterManager::GetInstance()->m_character[i]->m_ranking = i + 1;
		}
	}


	//-------------------------------------------------------------------------------------------------------
	//タイトル処理

	enum 
	{
		SINGLE_MODE = 0,
		VS_MODE,
		TITLE_MAX
	};


	bool title_pushAnyKey = false;
	int modeCommand = SINGLE_MODE;

	void GameManager::sceneTitle(float delta)
	{

		if (0.0f == _sequence.getTime())
		{

			printf("タイトルシーンが初期化されました\n");
			printf("\n");

			init();//ゲームの初期化

			title = new Moji(250.f, 250.f, { 20.f, 50.f }, { 1, 1, 1 }, "bmp/title/title.bmp");

			oka::SoundManager::GetInstance()->Play("TitleBGM");

		}

		glViewport(0, 0, g_window_width, g_window_height);

		//更新
		g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);

		//描画
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.f, 0.f, 0.f, 1.f);

		title->Draw();

		if (GameManager::m_flame % 60)
		{
			title->changeColor();
		}

		oka::SetLineWidth(5.0f);
		oka::DrawString("Bike", 105.0f, 180.0f, 0.3f);
		oka::DrawString("Racing", 85.0f, 135.0f, 0.3f);

		//シーンの遷移
		unsigned int aaa = oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey;

		if ((false == title_pushAnyKey) && (aaa & XINPUT_GAMEPAD_START))
		{
			title_pushAnyKey = true;
			oka::SoundManager::GetInstance()->Play("pushStartButtonSE");

		}

		if (false == title_pushAnyKey) {

			if ((GameManager::m_flame % 60) < 30)
			{
				oka::SetLineWidth(4.0f);
				oka::DrawString("PUSH START BUTTON", 75.0f, 40.0f, 0.1f);
			}

		}
		else
		{
			if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_yTopDown)
			{
				modeCommand++;
				modeCommand = (modeCommand + TITLE_MAX) % TITLE_MAX;
				oka::SoundManager::GetInstance()->Play("cursorMoveSE");

			}

			if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_yBottomDown)
			{
				modeCommand--;
				modeCommand = (modeCommand + TITLE_MAX) % TITLE_MAX;
				oka::SoundManager::GetInstance()->Play("cursorMoveSE");

			}


			if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
			{
				if (SINGLE_MODE == modeCommand)
				{
					//g_useController[0]->m_type = PLAYER;
				}

				else if (VS_MODE == modeCommand)
				{
					for (unsigned int i = 0; i < oka::JoysticManager::GetInstance()->GetConnectingNum(); i++)
					{
						//g_useController[i]->m_type = PLAYER;
					}

				}

				GameManager::GetInstance()->_sequence.change(&GameManager::sceneCourseSelect);
				oka::SoundManager::GetInstance()->Play("modeDecision");
			}

			oka::SetLineWidth(4.0f);
			if (SINGLE_MODE == modeCommand)
			{
				glColor3f(1, 0, 0);
				oka::DrawString("SINGLE MODE", 100.0f, 55.0f, 0.1f);
			}
			else
			{
				glColor3f(1, 1, 1);
				oka::DrawString("SINGLE MODE", 100.0f, 55.0f, 0.1f);
			}

			if (VS_MODE == modeCommand)
			{
				glColor3f(1, 0, 0);
				oka::DrawString("VS MODE", 115.0f, 25.0f, 0.1f);
			}
			else
			{
				glColor3f(1, 1, 1);
				oka::DrawString("VS MODE", 115.0f, 25.0f, 0.1f);
			}

			oka::SetDefaultLineWidth();
			oka::DrawString("[Lstick]CourseSelect", 200.0f, 5.0f, 0.05f);
			oka::DrawString("[A]Accept", 260.0f, 5.0f, 0.05f);
		}

		glFlush();

	}

	//-------------------------------------------------------------------------------------------------------
	//コース選択処理
	//RB LBでコースの選択をしてAでコース決定

	bool g_isCourseDecision = false;

	void GameManager::sceneCourseSelect(float delta) {

		if (0.0f == _sequence.getTime()) {
			printf("コースセレクトシーンが初期化されました\n");
			printf("\n");

			//アイテムの添え字初期化
			itemNum = 0;

			courseSelectBG = new Moji(300.f, 300.f, { 0.f, 0.f }, { 1, 1, 1 }, "bmp/courseSelect/courseSelectBG.bmp");
			courseSelect = new Moji(280.f, 70.f, { 18.f, 230.f }, { 0.f,1.f,0.f }, "bmp/courseSelect/courseSelect.bmp");
			course1_map = new Moji(240.f, 240.f, { 50.f, 10.f }, { 1, 1, 1 }, "bmp/courseSelect/course1_map.bmp");
			course2_map = new Moji(230.f, 200.f, { 55.f, 30.f }, { 1, 1, 1 }, "bmp/courseSelect/course2_map.bmp");


		}

		glViewport(0, 0, g_window_width, g_window_height);

		//更新
		g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);

		//描画
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.f, 0.f, 0.f, 1.f);

		if (g_isCourseDecision)
		{
			courseSelectBG->fadeOut();
			courseSelect->fadeOut();
			course1_map->fadeOut();
			course2_map->fadeOut();
		}

		//コースセレクト
		courseSelectBG->Draw();
		courseSelect->Draw();

		if (COURSE1 == selectedCourse) {

			//コースの様子
			course1_map->Draw();


		}
		else if (COURSE2 == selectedCourse) {

			course2_map->Draw();

		}

		//操作方法
		if (false == g_isCourseDecision)
		{
			oka::SetDefaultLineWidth();
			oka::DrawString("[Lstick]CourseSelect", 200.0f, 5.0f, 0.05f);
			oka::DrawString("[Lstick]CourseSelect", 260.0f, 5.0f, 0.05f);
		}

		if (false == g_isCourseDecision && oka::JoysticManager::GetInstance()->GetContoroller(0).m_xRightDown) {

			selectedCourse++;
			selectedCourse = (selectedCourse + COURSE_NUM_MAX) % COURSE_NUM_MAX;
			oka::SoundManager::GetInstance()->Play("cursorMoveSE");

		}

		if (false == g_isCourseDecision && oka::JoysticManager::GetInstance()->GetContoroller(0).m_xLeftDown) {

			selectedCourse--;
			selectedCourse = (selectedCourse + COURSE_NUM_MAX) % COURSE_NUM_MAX;
			oka::SoundManager::GetInstance()->Play("cursorMoveSE");

		}

		if (false == g_isCourseDecision && oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
		{

			g_isCourseDecision = true;

			oka::SoundManager::GetInstance()->Stop("TitleBGM");
			oka::SoundManager::GetInstance()->Play("courseDecision");



			//アイテム生成→コースの生成→アイテムの設置
			
			//アイテムの生成
			for (int i = 0; i < SET_ITEM_NUMBER; i++) 
			{
				oka::GameManager::GetInstance()->AddGameObject(new Item());
			}

			//コースの生成
			RaceManager::GetInstance()->m_course = createCourse();

			oka::GameManager::GetInstance()->AddGameObject(RaceManager::GetInstance()->m_course);



			//プレイヤーの初期座標決定
			if (COURSE1 == selectedCourse)
			{
				oka::SoundManager::GetInstance()->AddSound("Course1Bgm", oka::Sound::LoadWavFile("wav/course1BGM.wav"));
				oka::SoundManager::GetInstance()->ChangeVolume("Course1Bgm", 0.5f);

				oka::CharacterManager::GetInstance()->m_character[0]->m_transform.SetPosition(oka::Vec3(14.f, 0.0f, -165.f));
				oka::CharacterManager::GetInstance()->m_character[1]->m_transform.SetPosition(oka::Vec3(18.f, 0.f, -160.f));
				oka::CharacterManager::GetInstance()->m_character[2]->m_transform.SetPosition(oka::Vec3(22.f, 0.f, -155.f));
				oka::CharacterManager::GetInstance()->m_character[3]->m_transform.SetPosition(oka::Vec3(26.f, 0.f, -150.f));
			}
			else if (COURSE2 == selectedCourse)
			{
				oka::SoundManager::GetInstance()->AddSound("Course2Bgm", oka::Sound::LoadWavFile("wav/course2BGM.wav"));
				oka::SoundManager::GetInstance()->ChangeVolume("Course2Bgm", 0.5f);

				oka::CharacterManager::GetInstance()->m_character[0]->m_transform.SetPosition(oka::Vec3(17.f, 0.f, -110.5f));
				oka::CharacterManager::GetInstance()->m_character[1]->m_transform.SetPosition(oka::Vec3(25.f, 0.f, -105.5f));
				oka::CharacterManager::GetInstance()->m_character[2]->m_transform.SetPosition(oka::Vec3(33.f, 0.f, -100.5f));
				oka::CharacterManager::GetInstance()->m_character[3]->m_transform.SetPosition(oka::Vec3(41.f, 0.f, -95.5f));

			}

		}

		//プレイシーンに移行
		if (g_isCourseDecision && 0.f >= courseSelectBG->m_alpha)
		{
			GameManager::GetInstance()->_sequence.change(&GameManager::scenePlay);
		}


		glFlush();

	}



	/////////////

	void func(Character *_pCharacter) {

		 /*
		 
		 描画部分
		 	 
		 */

		//深度テスト
		glEnable(GL_DEPTH_TEST);

		//ライト
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		//debug
		/*for (int i = 0; i < CHECK_POINT_NUMBER; i++){
		  course->m_checkPoint[i].draw();
		}*/
		/*for (int i = 0; i < AI_POINT_NUMBER; i++){
		course->m_AIPoint[i].draw();
		}*/

		glDisable(GL_LIGHTING);






		for (unsigned int i = 0; i < GameManager::GetInstance()->m_gameObject.size(); i++)
		{
			GameManager::GetInstance()->m_gameObject[i]->Draw();
		}

		//車体部と車輪部のみライティングを有効にしてある
		//影部はライティング無効
		for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++) 
		{

			oka::CharacterManager::GetInstance()->m_character[i]->drawHasItem();

		}

		glDisable(GL_DEPTH_TEST);

		//煙の描画
		for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++) 
		{
			oka::CharacterManager::GetInstance()->m_character[i]->m_smoke.Draw();
		}

		//エフェクトの描画
		auto it = effect.begin();
		while (it != effect.end())
		{
			(*it)->Draw();
			++it;
		}

		/*更新*/
		g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);

		RaceManager::GetInstance()->CountRaceStart();
		RaceManager::GetInstance()->PrintRaceStrart();

		/*描画(2D)*/

		//順位の表示
		_pCharacter->printRanking();
		_pCharacter->printStatus();


	}

	//-------------------------------------------------------------------------------------------------------
	void GameManager::scenePlay(float delta)
	{
		if (0.0f == _sequence.getTime())
		{
			printf("プレイシーンが初期化されました\n");
			printf("\n");

			sprintf_s(str_lapMax, "%d", 3);

			//プレイヤーのエンジン音
			//player1->m_engine->play();
			//oka::SoundManager::GetInstance()->Play("Engine");

		}



		/********************************
		
		更新部分
		
		*********************************/

		//レースが始まったらする処理
		if (RaceManager::GetInstance()->m_raceStart) 
		{

			//順位の判定
			for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++)
			{
				std::sort(oka::CharacterManager::GetInstance()->m_character.begin(), oka::CharacterManager::GetInstance()->m_character.end(), checkRanking);
			}

			//順位の設定
			//実際に順位を付与する処理
			for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++)
			{
				oka::CharacterManager::GetInstance()->m_character[i]->m_ranking = i + 1;
			}


			for (unsigned int i = 0; i < CharacterManager::GetInstance()->m_character.size(); i++)
			{

				if (CharacterManager::GetInstance()->m_character[i]->m_contoroller.m_isConnect)
				{
					CharacterManager::GetInstance()->m_character[i]->control(
						CharacterManager::GetInstance()->m_character[i]->m_contoroller.m_state.Gamepad.wButtons,
						CharacterManager::GetInstance()->m_character[i]->m_contoroller.m_downkey,
						CharacterManager::GetInstance()->m_character[i]->m_contoroller.m_sThumbLX,
						CharacterManager::GetInstance()->m_character[i]->m_contoroller.m_sThumbLY);

				}
				else
				{
					CharacterManager::GetInstance()->m_character[i]->control();
				}

			}


			//全オブジェクトのUpdate
			for (unsigned int i = 0; i < oka::GameManager::GetInstance()->m_gameObject.size(); i++)
			{
				oka::GameManager::GetInstance()->m_gameObject[i]->Update();
			}



		






			//接触判定
			for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++) {
				for (unsigned int t = i + 1; t < CharacterManager::GetInstance()->GetCharacterNumber(); t++) {

					//前輪と前輪
					if (isHitCharacter(oka::CharacterManager::GetInstance()->m_character[i]->m_frontPosition, oka::CharacterManager::GetInstance()->m_character[t]->m_frontPosition) ||

						//前輪と後輪
						isHitCharacter(oka::CharacterManager::GetInstance()->m_character[i]->m_frontPosition, oka::CharacterManager::GetInstance()->m_character[t]->m_backPosition) ||

						//後輪と前輪
						isHitCharacter(oka::CharacterManager::GetInstance()->m_character[i]->m_backPosition, oka::CharacterManager::GetInstance()->m_character[t]->m_frontPosition) ||

						//後輪と後輪
						isHitCharacter(oka::CharacterManager::GetInstance()->m_character[i]->m_frontPosition, oka::CharacterManager::GetInstance()->m_character[t]->m_frontPosition)) {

						//1フレーム前の座標に戻して進行方向とは
						//逆のベクトルを足し込む
						oka::Vec3 reverse = oka::CharacterManager::GetInstance()->m_character[i]->m_transform.GetPosition() - oka::CharacterManager::GetInstance()->m_character[t]->m_transform.GetPosition();
						oka::CharacterManager::GetInstance()->m_character[i]->m_speed += reverse*0.01f;
						oka::CharacterManager::GetInstance()->m_character[t]->m_speed -= reverse*0.01f;
					}
				}
			}

		}


		//エフェクトの更新
		std::list<Effect*>::iterator it = effect.begin();
		it = effect.begin();
		while (it != effect.end())
		{
			(*it)->Update();
			(*it)->checkCourseOut();
			++it;
		}

		//エフェクト削除処理
		it = effect.begin();
		while (it != effect.end()) {

			if (false == (*it)->m_isActive) {
				it = effect.erase(it);
				continue;
			}

			it++;

		}


		//-------------------------------------
		//描画(3D)

		if (SINGLE_MODE == modeCommand) 
		{

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glClearColor(77.f / 255.f, 180.f / 255.f, 232.f / 255.f, 1);

			oka::Vec3 pos;
			pos.m_x = oka::CharacterManager::GetInstance()->m_character[0]->m_transform.GetPosition().m_x + sin(oka::CharacterManager::GetInstance()->m_character[0]->m_transform.GetRotation().m_y) * 8;
			pos.m_y = oka::CharacterManager::GetInstance()->m_character[0]->m_transform.GetPosition().m_y + 3.5f;
			pos.m_z = oka::CharacterManager::GetInstance()->m_character[0]->m_transform.GetPosition().m_z + cos(oka::CharacterManager::GetInstance()->m_character[0]->m_transform.GetRotation().m_y) * 8;

			oka::Vec3 target;
			target = oka::CharacterManager::GetInstance()->m_character[0]->m_transform.GetPosition();

			oka::Vec3 up = oka::Vec3(0, 1, 0);

			g_camera->Perspective();
			g_camera->SetViewMatrix(pos, target, up);
			g_camera->MultViewMatrix();

			func(oka::CharacterManager::GetInstance()->m_character[0]);

			glFlush();

		}

		else if (VS_MODE == modeCommand)
		{

			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//glClearColor(77.f / 255.f, 180.f / 255.f, 232.f / 255.f, 1);

			////左上
			//glViewport(0, g_window_height / 2, g_window_width / 2, g_window_height / 2);
			//g_camera->SetPosition({
			//	player1->transform.m_position.m_x + sin(player1->transform.m_rotate.m_y) * 8,
			//	player1->transform.m_position.m_y + 3.5f,
			//	player1->transform.m_position.m_z + cos(player1->transform.m_rotate.m_y) * 8
			//});
			//g_camera->SetTarget({ player1->transform.m_position });
			//g_camera->update(TYPE_3D);

			//func(player1);

			////右上
			//glViewport(g_window_width / 2, g_window_height / 2, g_window_width / 2, g_window_height / 2);
			//g_camera->SetPosition({
			//	player2->transform.m_position.m_x + sin(player2->transform.m_rotate.m_y) * 8,
			//	player2->transform.m_position.m_y + 3.5f,
			//	player2->transform.m_position.m_z + cos(player2->transform.m_rotate.m_y) * 8
			//});
			//g_camera->SetTarget({ player2->transform.m_position });
			//g_camera->update(TYPE_3D);

			//func(player2);

			////左下
			//glViewport(0, 0, g_window_width / 2, g_window_height / 2);
			//g_camera->SetPosition({
			//	player3->transform.m_position.m_x + sin(player3->transform.m_rotate.m_y) * 8,
			//	player3->transform.m_position.m_y + 3.5f,
			//	player3->transform.m_position.m_z + cos(player3->transform.m_rotate.m_y) * 8
			//});
			//g_camera->SetTarget({ player3->transform.m_position });
			//g_camera->update(TYPE_3D);

			//func(player3);

			////右下
			//glViewport(g_window_width / 2, 0, g_window_width / 2, g_window_height / 2);
			//g_camera->SetPosition({
			//	player4->transform.m_position.m_x + sin(player4->transform.m_rotate.m_y) * 8,
			//	player4->transform.m_position.m_y + 3.5f,
			//	player4->transform.m_position.m_z + cos(player4->transform.m_rotate.m_y) * 8
			//});
			//g_camera->SetTarget({ player4->transform.m_position });
			//g_camera->update(TYPE_3D);

			//func(player4);

			//glFlush();

		}

		if (true == (oka::CharacterManager::GetInstance()->m_character[0]->m_isGoal && oka::CharacterManager::GetInstance()->m_character[1]->m_isGoal &&
			oka::CharacterManager::GetInstance()->m_character[2]->m_isGoal && oka::CharacterManager::GetInstance()->m_character[3]->m_isGoal))
		{
			//スタートボタンが押されたら
			//タイトルシーンに移行
			if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_START)
			{
				GameManager::GetInstance()->_sequence.change(&GameManager::sceneTitle);

				title_pushAnyKey = false;
				g_isCourseDecision = false;
				modeCommand = SINGLE_MODE;

				//コースbgm停止
				//course->m_bgm->stop();

				//エンジン音を止める
				//player1->m_engine->stop();

				//ループに必要な初期化処理
				//startRace = false;
				//startFrame = 0;//フレーム数
				//timenow = 0;//経過時間
				//timebase = 0;//計測開始時間
				//startCount = 6;

				//周回数表示クリア
				memset(str_lapMax, 0, sizeof(str_lapMax));

				//キャラクター削除
				/*for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++) {

					delete character[i];

				}
				character.clear();*/

				//エフェクト削除
				effect.clear();

			}

		}
	}

}