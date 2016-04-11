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

//-------------------------------------
//現在選択されているゲームモード初期化

int TitleScene::m_gameMode = single;

//-------------------------------------
//ゲームモード名の配列初期化

const char* TitleScene::m_gameModeName[GameModeMax] =
{
	"Single Mode",
	"VS Mode",
	"Exit"
};

void TitleScene::Update()
{
	//if ((oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_START))
	//{
	//	oka::SoundManager::GetInstance()->Play("pushStartButtonSE");//鳴らない
	//}

	if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_yBottomDown)
		{
			m_gameMode++;
			m_gameMode = (m_gameMode + TitleScene::GameMode::GameModeMax) % TitleScene::GameMode::GameModeMax;
			oka::SoundManager::GetInstance()->Play("cursorMoveSE");

		}

		if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_yTopDown)
		{
			m_gameMode--;
			m_gameMode = (m_gameMode + TitleScene::GameMode::GameModeMax) % TitleScene::GameMode::GameModeMax;
			oka::SoundManager::GetInstance()->Play("cursorMoveSE");

		}

}

void TitleScene::Render()
{
	glViewport(0, 0, oka::ScreenManager::GetInstance()->GetWidth(), oka::ScreenManager::GetInstance()->GetHeight());

	//更新
	g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);


	//文字描画変えたい
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

	for (int i = 0; i < GameModeMax; i++)
	{
		glm::vec2 pos = glm::vec2(110.0f, 80.0f - 20.0f*i);
		scale = 0.1f;
		width = 2.0f;

		if (m_gameMode == i)
		{
			color = oka::Vec3(1.0f, 0.0f, 0.0f);
		}
		else
		{
			color = oka::Vec3(1.0f, 1.0f, 1.0f);
		}

		oka::DrawString(m_gameModeName[i], pos, scale, color, width);

	}
}