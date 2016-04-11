#include"CourseSelectScene.h"

#include"Camera.h"
#include"GameManager.h"
#include"ScreenManager.h"
#include"JoysticManager.h"
#include"SoundManager.h"
#include"CharacterManager.h"
#include"ImageManager.h"
#include"ItemManager.h"
#include"RaceManager.h"
#include"StrokeString.h"

//変更予定

CourseSelectScene::CourseSelectScene()
{
	//debug
	printf("コース選択シーン生成\n");
	printf("\n");

	m_rot = 0.0f;

	m_selectedCourse = Course1;
	
	m_course[Course1] = new Course();
	m_course[Course1]->m_name = "Course1";
	m_course[Course1]->m_handle = oka::ImageManager::GetInstance()->GetHandle("Course1");

	m_course[Course2] = new Course();
	m_course[Course2]->m_name = "Course2";
	m_course[Course2]->m_handle = oka::ImageManager::GetInstance()->GetHandle("Course2");

}

void CourseSelectScene::Update()
{
	if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_yBottomDown) 
	{
		m_rot = 0.0f;

		m_selectedCourse++;
		m_selectedCourse = (m_selectedCourse + CourseName::CourseNameMax) % CourseName::CourseNameMax;
		oka::SoundManager::GetInstance()->Play("cursorMoveSE");

	}

	if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_yTopDown) 
	{
		m_rot = 0.0f;

		m_selectedCourse--;
		m_selectedCourse = (m_selectedCourse + CourseName::CourseNameMax) % CourseName::CourseNameMax;
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
			newCourse = new Course();
			newCourse->m_handle = oka::ImageManager::GetInstance()->GetHandle("Course1");
			newCourse->SetCheckPoint("txt/course1_cp.txt");		
			newCourse->SetAimPoint("txt/course1_AIp.txt");
			newCourse->MakeBuffer("bmp/course1/buffer1.bmp");
			newCourse->SetItem();

			newCourse->m_bgm = oka::SoundManager::GetInstance()->GetHandle("Course1BGM");

			//初期座標
			CharacterManager::GetInstance()->m_character[0]->m_transform.SetPosition(oka::Vec3(14.f, 0.0f, -165.f));
			CharacterManager::GetInstance()->m_character[1]->m_transform.SetPosition(oka::Vec3(18.f, 0.f, -160.f));
			CharacterManager::GetInstance()->m_character[2]->m_transform.SetPosition(oka::Vec3(22.f, 0.f, -155.f));
			CharacterManager::GetInstance()->m_character[3]->m_transform.SetPosition(oka::Vec3(26.f, 0.f, -150.f));

		}

		else if (CourseName::Course2 == m_selectedCourse)
		{
			newCourse = new Course();
			newCourse->m_handle = oka::ImageManager::GetInstance()->GetHandle("Course2");
			newCourse->SetCheckPoint("txt/course2_cp.txt");
			newCourse->SetAimPoint("txt/course2_AIp.txt");
			newCourse->MakeBuffer("bmp/course2/buffer2.bmp");
			newCourse->SetItem();

			newCourse->m_bgm = oka::SoundManager::GetInstance()->GetHandle("Course2BGM");

			//初期座標
			CharacterManager::GetInstance()->m_character[0]->m_transform.SetPosition(oka::Vec3(17.f, 0.f, -110.5f));
			CharacterManager::GetInstance()->m_character[1]->m_transform.SetPosition(oka::Vec3(25.f, 0.f, -105.5f));
			CharacterManager::GetInstance()->m_character[2]->m_transform.SetPosition(oka::Vec3(33.f, 0.f, -100.5f));
			CharacterManager::GetInstance()->m_character[3]->m_transform.SetPosition(oka::Vec3(41.f, 0.f, -95.5f));

		}

		RaceManager::GetInstance()->m_course = newCourse;
		oka::GameManager::GetInstance()->AddGameObject(RaceManager::GetInstance()->m_course);

	}

}

void CourseSelectScene::Render()
{
	//設定必要？
	//ビューポートの設定
	/*const int x = 0;
	const int y = 0;
	const int width = oka::ScreenManager::GetInstance()->GetWidth();
	const int height = oka::ScreenManager::GetInstance()->GetHeight();

	oka::ScreenManager::GetInstance()->SetViewport(x, y, width, height);*/

	m_rot += 0.01f;

	float x = sin(m_rot)*100 + 200.0f;
	float z = cos(m_rot)*50 + 100.0f;

	oka::Vec3 position = oka::Vec3(x, 150.0f, z);
	oka::Vec3 target = oka::Vec3(128.0f, 0.0f, -128.0f);
	oka::Vec3 up = oka::Vec3(0.0f, 1.0f, 0.0f);

	g_camera->Perspective();
	g_camera->SetViewMatrix(position, target, up);
	g_camera->MultViewMatrix();

	m_course[m_selectedCourse]->Draw();

	//更新
	g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);

	glm::vec2 pos = glm::vec2(55.0f,250.0f);
	oka::Vec3 color = oka::Vec3(1.0f,1.0f,1.0f);
	float scale = 0.25f;
	float width = 3.0f;

	oka::DrawString("CourseSelect",pos, scale,color, width);

	for (int i = 0; i < CourseNameMax; i++) 
	{
		pos = glm::vec2(120.0f, 200.0f - 30.0f*i);
		scale = 0.15f;
		width = 3.0f;

		if (m_selectedCourse == i)
		{
			color = oka::Vec3(1.0f, 0.0f, 0.0f);
		}
		else
		{
			color = oka::Vec3(1.0f, 1.0f, 1.0f);
		}

		oka::DrawString(m_course[i]->m_name, pos, scale, color, width);

	}

}