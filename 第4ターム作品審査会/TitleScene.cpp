#include"TitleScene.h"


#include<stdio.h>

#include"GameManager.h"
#include"sequence.h"
#include"Camera.h"

#include"CharacterManager.h"
#include"SoundManager.h"
#include"JoysticManager.h"
#include"RaceManager.h"
#include"TimeManager.h"
#include"ScreenManager.h"
#include"StrokeString.h"
#include"glm\glm.hpp"
#include"Vec3.h"

bool title_pushAnyKey = false;

void TitleScene::Update()
{
	if ((false == title_pushAnyKey) && (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_START))
	{
		title_pushAnyKey = true;
		oka::SoundManager::GetInstance()->Play("pushStartButtonSE");

	}

}

void TitleScene::Render()
{
	glViewport(0, 0, oka::ScreenManager::GetInstance()->GetWidth(), oka::ScreenManager::GetInstance()->GetHeight());

	//XV
	g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);


	//•¶Žš•`‰æ•Ï‚¦‚½‚¢
	glm::vec2 position = glm::vec2(70.0f, 180.0f);
	float scale = 0.3f;
	oka::Vec3 color = oka::Vec3(1.0f, 1.0f, 1.0f);
	float width = 5.0f;

	oka::DrawString("Bike", position, scale, color, width);

	position = glm::vec2(110.0f, 135.0f);
	scale = 0.3f;
	color = oka::Vec3(1.0f, 1.0f, 1.0f);
	width = 5.0f;

	oka::DrawString("Racing", position, scale, color, width);

	if (false == title_pushAnyKey)
	{

		if ((oka::TimeManager::GetInstance()->m_flame % 60) < 30)
		{
			glm::vec2 position = glm::vec2(85.0f, 40.0f);
			float scale = 0.1f;
			oka::Vec3 color = oka::Vec3(1.0f, 1.0f, 1.0f);
			float width = 1.5f;

			oka::DrawString("Push Start Button", position, scale, color, width);
		}

	}
	else
	{
		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_yTopDown)
		{
			m_mode++;
			m_mode = (m_mode + TitleScene::Mode::Max) % TitleScene::Mode::Max;
			oka::SoundManager::GetInstance()->Play("cursorMoveSE");

		}

		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_yBottomDown)
		{
			m_mode--;
			m_mode = (m_mode + TitleScene::Mode::Max) % TitleScene::Mode::Max;
			oka::SoundManager::GetInstance()->Play("cursorMoveSE");

		}


		/*if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_A)
		{
			oka::GameManager::GetInstance()->_sequence.Change(&oka::GameManager::sceneCourseSelect);
			oka::SoundManager::GetInstance()->Play("modeDecision");
		}*/

		//oka::SetLineWidth(4.0f);
		if (TitleScene::Mode::Single == m_mode)
		{
			glm::vec2 position = glm::vec2(100.0f, 55.0f);
			float scale = 0.1f;
			oka::Vec3 color = oka::Vec3(1.0f, 0.0f, 0.0f);
			float width = 1.0f;

			oka::DrawString("Single Mode", position, scale, color, width);
		}
		else
		{
			glm::vec2 position = glm::vec2(100.0f, 55.0f);
			float scale = 0.1f;
			oka::Vec3 color = oka::Vec3(1.0f, 1.0f, 1.0f);
			float width = 1.0f;

			oka::DrawString("Single Mode", position, scale, color, width);
		}

		if (TitleScene::Mode::Vs == m_mode)
		{
			glm::vec2 position = glm::vec2(115.0f, 25.0f);
			float scale = 0.1f;
			oka::Vec3 color = oka::Vec3(1.0f, 0.0f, 0.0f);
			float width = 1.0f;

			oka::DrawString("Vs Mode", position, scale, color, width);
		}
		else
		{
			glm::vec2 position = glm::vec2(115.0f, 25.0f);
			float scale = 0.1f;
			oka::Vec3 color = oka::Vec3(1.0f, 1.0f, 1.0f);
			float width = 1.0f;

			oka::DrawString("Vs Mode", position, scale, color, width);
		}
	}

}