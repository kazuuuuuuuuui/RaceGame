#include"CourseSelectScene.h"

#include"Camera.h"
#include"GameManager.h"
#include"ScreenManager.h"
#include"JoysticManager.h"
#include"SoundManager.h"
#include"CharacterManager.h"
#include"ItemManager.h"
#include"RaceManager.h"

void CourseSelectScene::Update()
{
	if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_xRightDown) {

		m_selectedCourse++;
		m_selectedCourse = (m_selectedCourse + CourseName::Max) % CourseName::Max;
		oka::SoundManager::GetInstance()->Play("cursorMoveSE");

	}

	if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_xLeftDown) {

		m_selectedCourse--;
		m_selectedCourse = (m_selectedCourse + CourseName::Max) % CourseName::Max;
		oka::SoundManager::GetInstance()->Play("cursorMoveSE");

	}

	if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
	{
		oka::SoundManager::GetInstance()->Stop("TitleBGM");
		oka::SoundManager::GetInstance()->Play("courseDecision");


		//アイテム生成→コースの生成→アイテムの設置

		//アイテムの生成
		for (unsigned int i = 0; i < ItemManager::GetInstance()->m_item.size(); i++)
		{
			oka::GameManager::GetInstance()->AddGameObject(ItemManager::GetInstance()->m_item[i]);
		}

		//コースの生成

		/*
		
		後々書き換え
		
		*/

		Course *newCourse = nullptr;

		if (CourseName::Course1 == m_selectedCourse)
		{
			newCourse = new Course("bmp/course1/course1.bmp");
			newCourse->SetCheckPoint("txt/course1_cp.txt");		
			newCourse->SetAimPoint("txt/course1_AIp.txt");
			newCourse->MakeBuffer("bmp/course1/buffer1.bmp");
			newCourse->SetItem();

			//レースのBGM読み込み
			newCourse->m_bgm = oka::Sound::LoadWavFile("wav/course1BGM.wav");

			//初期座標
			CharacterManager::GetInstance()->m_character[0]->m_transform.SetPosition(oka::Vec3(14.f, 0.0f, -165.f));
			CharacterManager::GetInstance()->m_character[1]->m_transform.SetPosition(oka::Vec3(18.f, 0.f, -160.f));
			CharacterManager::GetInstance()->m_character[2]->m_transform.SetPosition(oka::Vec3(22.f, 0.f, -155.f));
			CharacterManager::GetInstance()->m_character[3]->m_transform.SetPosition(oka::Vec3(26.f, 0.f, -150.f));

		}

		else if (CourseName::Course2 == m_selectedCourse)
		{
			newCourse = new Course("bmp/course2/course2.bmp");
			newCourse->SetCheckPoint("txt/course2_cp.txt");
			newCourse->SetAimPoint("txt/course2_AIp.txt");
			newCourse->MakeBuffer("bmp/course2/buffer2.bmp");
			newCourse->SetItem();

			//レースのBGM読み込み
			newCourse->m_bgm = oka::Sound::LoadWavFile("wav/course2BGM.wav");

			//初期座標
			CharacterManager::GetInstance()->m_character[0]->m_transform.SetPosition(oka::Vec3(17.f, 0.f, -110.5f));
			CharacterManager::GetInstance()->m_character[1]->m_transform.SetPosition(oka::Vec3(25.f, 0.f, -105.5f));
			CharacterManager::GetInstance()->m_character[2]->m_transform.SetPosition(oka::Vec3(33.f, 0.f, -100.5f));
			CharacterManager::GetInstance()->m_character[3]->m_transform.SetPosition(oka::Vec3(41.f, 0.f, -95.5f));

		}

		/**/

		RaceManager::GetInstance()->m_course = newCourse;
		oka::GameManager::GetInstance()->AddGameObject(RaceManager::GetInstance()->m_course);

	}

}

void CourseSelectScene::Render()
{
	//ビューポートの設定
	const int x = 0;
	const int y = 0;
	const int width = oka::ScreenManager::GetInstance()->GetWidth();
	const int height = oka::ScreenManager::GetInstance()->GetHeight();

	oka::ScreenManager::GetInstance()->SetViewport(x, y, width, height);

	//更新
	g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);

}