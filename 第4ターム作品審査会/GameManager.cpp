/*

�L�����i�[�Ə��ʕt����x�N�^�[�𕪂���K�v�L��H


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
#include"Sound.h"
#include"glut.h"

unsigned int threeTexture = 0;
unsigned int twoTexture = 0;

unsigned int oneTexture = 0;
unsigned int goTexture = 0;
unsigned int goalTexture = 0;

unsigned int rank1st = 0;
unsigned int rank2nd = 0;
unsigned int rank3rd = 0;
unsigned int rank4th = 0;

//debug
extern int g_window_width;
extern int g_window_height;

//��芸����
int startFrame = 0;//�t���[����
int timenow = 0;//�o�ߎ���
int timebase = 0;//�v���J�n����
int startCount = 6;

//���񐔕\���Ɏg��
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
	//���[�X���n�܂��Ă��邩�̃t���O
	bool startRace = false;

	GameManager* GameManager::m_instance = nullptr;

	//-------------------------------------------------------------------------------------------------------
	//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
	//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�


	GameManager* GameManager::GetInstance()
	{
		if (nullptr == m_instance) 
		{
			m_instance = new GameManager();
		}
		return m_instance;
	}


	//-------------------------------------
	//�Q�[���Ɍ����I�u�W�F�N�g�̒ǉ�
	//�Ǘ����Ă���}�b�v�Ɋ��ɓo�^����Ă��錟����
	//�o�^����Ă��Ȃ���Βǉ�����

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






























	//�ڐG����
	//��芸����
	bool isHitCharacter(oka::Vec3 _myPos, oka::Vec3 _youPos) {

		oka::Vec3 v = _myPos - _youPos;

		float hitLine = 2.4f;

		if (v.length() < hitLine) {
			return true;
		}

		return false;

	}

	//���ʔ���p�̊֐�
	//���ʂ̔���݂̂���
	bool checkRanking(Character *_character1, Character *_character2)
	{

		//���񐔂ł̔���
		if (_character1->m_lapCount > _character2->m_lapCount)
		{
			return true;
		}
		else if (_character1->m_lapCount < _character2->m_lapCount)
		{
			return false;
		}

		//�`�F�b�N�|�C���g�̐i�݋�ł̔���
		if (_character1->m_nowPoint > _character2->m_nowPoint)
		{
			return true;
		}
		else if (_character1->m_nowPoint < _character2->m_nowPoint)
		{
			return false;
		}

		//�ڎw���Ă���`�F�b�N�|�C���g�ւ̋����ł̔���
		if (_character1->m_nextCheckPointLength > _character2->m_nextCheckPointLength)
		{
			return false;
		}
		else if (_character1->m_nextCheckPointLength < _character2->m_nextCheckPointLength)
		{
			return true;
		}

		//��芸���������Ԃ�
		return false;

	}


	//-------------------------------------
	//���[�X�X�^�[�g�̃J�E���g�_�E��
	void countRaceStart()
	{

		startFrame++; //�t���[�������{�P

		timenow = glutGet(GLUT_ELAPSED_TIME);//�o�ߎ��Ԃ��擾

		if (timenow - timebase > 1000)      //�P�b�ȏソ�����珈�����s��
		{
			startCount--;

			if (0 == startCount) {

				//�J�E���g�_�E�����I��������
				//���[�X���J�n����Ă��邩�̃t���O�𗧂Ă�
				startRace = true;

			}

			timebase = timenow;//����Ԃ�ݒ�                
			startFrame = 0;//�t���[���������Z�b�g
		}

		//�J�E���g�_�E���̉�
		if (3 == startCount && startFrame == 0)
		{
			oka::SoundManager::GetInstance()->Play("CountDown");
		}
		if (3 == startCount && startFrame == 30)
		{
			oka::SoundManager::GetInstance()->Stop("CountDown");
		}

		if (2 == startCount && startFrame == 0)
		{
			oka::SoundManager::GetInstance()->Play("CountDown");
		}
		if (2 == startCount && startFrame == 30)
		{
			oka::SoundManager::GetInstance()->Stop("CountDown");
		}

		if (1 == startCount && startFrame == 0)
		{
			oka::SoundManager::GetInstance()->Play("CountDown");
		}
		if (1 == startCount && startFrame == 30)
		{
			oka::SoundManager::GetInstance()->Stop("CountDown");
		}

		if (0 == startCount && startFrame == 0)
		{
			oka::SoundManager::GetInstance()->ChangePitch("CountDown", 2.0f);
			oka::SoundManager::GetInstance()->Play("CountDown");
		}

		if (-1 == startCount && startFrame == 10)
		{
			oka::SoundManager::GetInstance()->Stop("CountDown");
			//course->m_bgm->play();
		}


	}

	void printRaceStart() {

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (startCount <= 3 && startCount > 0) {
			glPushMatrix();
			{
				glTranslatef(100, 100, 0);

				if (startCount == 3) {
					glBindTexture(GL_TEXTURE_2D, threeTexture);

				}
				else if (startCount == 2) {
					glBindTexture(GL_TEXTURE_2D, twoTexture);
				}
				else if (startCount == 1) {
					glBindTexture(GL_TEXTURE_2D, oneTexture);
				}

				glColor4f(1, 1, 1, 1);

				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);
					glVertex2f(0, 0);

					glTexCoord2f(1, 1);
					glVertex2f(100, 0);

					glTexCoord2f(1, 0);
					glVertex2f(100, 100);

					glTexCoord2f(0, 0);
					glVertex2f(0, 100);
				}
				glEnd();
			}
			glPopMatrix();

		}
		else if (0 == startCount) {

			static float num = 1.f;
			num += 0.007f;

			glPushMatrix();
			{
				glBindTexture(GL_TEXTURE_2D, goTexture);

				glTranslatef(150, 150, 0);
				glScalef(num, num, num);
				glColor4f(1, 1, 1, 1);

				glBegin(GL_QUADS);
				{
					glTexCoord2f(0, 1);
					glVertex2f(-50, -50);

					glTexCoord2f(1, 1);
					glVertex2f(50, -50);

					glTexCoord2f(1, 0);
					glVertex2f(50, 50);

					glTexCoord2f(0, 0);
					glVertex2f(-50, 50);
				}
				glEnd();
			}
			glPopMatrix();

		}

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

	}


	//-------------------------------------
	//�Q�[���̏������S�ʂ��s��

	void init()
	{
		oka::CharacterManager::GetInstance();

		//�R���g���[���[�̑Ή��t��
		for (unsigned int i = 0; i<oka::CharacterManager::GetInstance()->GetCharacterNumber();i++)
		{
			oka::JoysticManager::GetInstance()->AddController(oka::CharacterManager::GetInstance()->m_character[i]->m_contoroller);
		}

		//�L�����N�^�[�̓o�^
		for (unsigned int i = 0; i<oka::CharacterManager::GetInstance()->GetCharacterNumber(); i++)
		{
			oka::GameManager::GetInstance()->AddGameObject(oka::CharacterManager::GetInstance()->m_character[i]);
		}

		
		
		
		//�J�����̐���
		g_camera = new oka::Camera();

		//�e�N�X�`���̓ǂݍ���

		//�g�p���閂�΂̃e�N�X�`���ǂݍ���
		oka::ImageManager::GetInstance()->SetHandle("ItemFire", oka::BmpImage::LoadImage3f("bmp/getItem/fire.bmp"));
		oka::ImageManager::GetInstance()->SetHandle("ItemBlizzard", oka::BmpImage::LoadImage3f("bmp/getItem/blizzard.bmp"));

		threeTexture = oka::BmpImage::LoadImage4f("bmp/start/three.bmp");
		twoTexture = oka::BmpImage::LoadImage4f("bmp/start/two.bmp");
		oneTexture = oka::BmpImage::LoadImage4f("bmp/start/one.bmp");
		goTexture = oka::BmpImage::LoadImage4f("bmp/start/go.bmp");
		goalTexture = oka::BmpImage::LoadImage4f("bmp/goal.bmp");

		smoke_handle = oka::BmpImage::LoadImage4f("bmp/Effect/smoke.bmp");
		dash_handle = oka::BmpImage::LoadImage4f("bmp/Effect/dash.bmp");

		rank1st = oka::BmpImage::LoadImage4f("bmp/Ranking/1st.bmp");
		rank2nd = oka::BmpImage::LoadImage4f("bmp/Ranking/2nd.bmp");
		rank3rd = oka::BmpImage::LoadImage4f("bmp/Ranking/3rd.bmp");
		rank4th = oka::BmpImage::LoadImage4f("bmp/Ranking/4th.bmp");

		dashIcon = oka::BmpImage::LoadImage4f("bmp/dashIcon.bmp");
		dashGauge = oka::BmpImage::LoadImage4f("bmp/gauge.bmp");

		EffectBlizzard = oka::BmpImage::LoadImage4f("bmp/Effect/blizzard.bmp");



		//�g�p���鉹�ǂݍ���	
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


		//�ŏ��̏��ʐݒ�Ə��ʕt�^
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
	//�^�C�g������

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

			printf("�^�C�g���V�[��������������܂���\n");
			printf("\n");

			init();//�Q�[���̏�����

			title = new Moji(250.f, 250.f, { 20.f, 50.f }, { 1, 1, 1 }, "bmp/title/title.bmp");

			oka::SoundManager::GetInstance()->Play("TitleBGM");

		}

		glViewport(0, 0, g_window_width, g_window_height);

		//�X�V
		g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);

		//�`��
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

		//�V�[���̑J��
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
	//�R�[�X�I������
	//RB LB�ŃR�[�X�̑I��������A�ŃR�[�X����

	bool g_isCourseDecision = false;

	void GameManager::sceneCourseSelect(float delta) {

		if (0.0f == _sequence.getTime()) {
			printf("�R�[�X�Z���N�g�V�[��������������܂���\n");
			printf("\n");

			//�A�C�e���̓Y����������
			itemNum = 0;

			courseSelectBG = new Moji(300.f, 300.f, { 0.f, 0.f }, { 1, 1, 1 }, "bmp/courseSelect/courseSelectBG.bmp");
			courseSelect = new Moji(280.f, 70.f, { 18.f, 230.f }, { 0.f,1.f,0.f }, "bmp/courseSelect/courseSelect.bmp");
			course1_map = new Moji(240.f, 240.f, { 50.f, 10.f }, { 1, 1, 1 }, "bmp/courseSelect/course1_map.bmp");
			course2_map = new Moji(230.f, 200.f, { 55.f, 30.f }, { 1, 1, 1 }, "bmp/courseSelect/course2_map.bmp");


		}

		glViewport(0, 0, g_window_width, g_window_height);

		//�X�V
		g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);

		//�`��
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.f, 0.f, 0.f, 1.f);

		if (g_isCourseDecision)
		{
			courseSelectBG->fadeOut();
			courseSelect->fadeOut();
			course1_map->fadeOut();
			course2_map->fadeOut();
		}

		//�R�[�X�Z���N�g
		courseSelectBG->Draw();
		courseSelect->Draw();

		if (COURSE1 == selectedCourse) {

			//�R�[�X�̗l�q
			course1_map->Draw();


		}
		else if (COURSE2 == selectedCourse) {

			course2_map->Draw();

		}

		//������@
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



			//�A�C�e���������R�[�X�̐������A�C�e���̐ݒu
			//�A�C�e���̐���
			for (int i = 0; i < SET_ITEM_NUMBER; i++) 
			{
				oka::GameManager::GetInstance()->AddGameObject(new Item());
			}

			



			//�R�[�X�̐���
			course = createCourse();

			//�v���C���[�̏������W����
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

		//�v���C�V�[���Ɉڍs
		if (g_isCourseDecision && 0.f >= courseSelectBG->m_alpha)
		{
			GameManager::GetInstance()->_sequence.change(&GameManager::scenePlay);
		}


		glFlush();

	}



	/////////////

	void func(Character *_pCharacter) {

		//�[�x�e�X�g
		glEnable(GL_DEPTH_TEST);

		//���C�g
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		course->draw();

		//debug
		/*for (int i = 0; i < CHECK_POINT_NUMBER; i++){
		  course->m_checkPoint[i].draw();
		}*/
		/*for (int i = 0; i < AI_POINT_NUMBER; i++){
		course->m_AIPoint[i].draw();
		}*/

		glDisable(GL_LIGHTING);

		//�ԑ̕��Ǝԗ֕��̂݃��C�e�B���O��L���ɂ��Ă���
		//�e���̓��C�e�B���O����
		for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++)
		{
			oka::CharacterManager::GetInstance()->m_character[i]->Draw();
		}

		/*for (int i = 0; i < SET_ITEM_NUMBER; i++)
		{
			item[i]->Draw();
		}*/

		for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++) 
		{

			oka::CharacterManager::GetInstance()->m_character[i]->drawHasItem();

		}

		glDisable(GL_DEPTH_TEST);

		//���̕`��
		for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++) 
		{

			oka::CharacterManager::GetInstance()->m_character[i]->m_smoke.Draw();

		}

		//�G�t�F�N�g�̕`��
		auto it = effect.begin();
		while (it != effect.end())
		{
			(*it)->Draw();
			++it;
		}

		/*�X�V*/
		g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);

		countRaceStart();
		printRaceStart();

		/*�`��(2D)*/

		//���ʂ̕\��
		_pCharacter->printRanking();
		_pCharacter->printStatus();


	}

	//-------------------------------------------------------------------------------------------------------
	void GameManager::scenePlay(float delta)
	{
		if (0.0f == _sequence.getTime())
		{
			printf("�v���C�V�[��������������܂���\n");
			printf("\n");

			sprintf_s(str_lapMax, "%d", 3);

			//�v���C���[�̃G���W����
			//player1->m_engine->play();
			//oka::SoundManager::GetInstance()->Play("Engine");

		}



		/********************************
		
		�X�V����
		
		*********************************/

		//���[�X���n�܂����炷�鏈��
		if (true == startRace) {

			//���ʂ̔���
			for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++)
			{
				std::sort(oka::CharacterManager::GetInstance()->m_character.begin(), oka::CharacterManager::GetInstance()->m_character.end(), checkRanking);
			}

			//���ʂ̐ݒ�
			//���ۂɏ��ʂ�t�^���鏈��
			for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++)
			{
				oka::CharacterManager::GetInstance()->m_character[i]->m_ranking = i + 1;
			}

			for (unsigned int i = 0; i < oka::JoysticManager::GetInstance()->GetConnectingNum(); i++)
			{

				if (oka::JoysticManager::GetInstance()->GetContoroller(i).m_isConnect)
				{

					/*

					��Ŏ���

					*/



					/*control(
						oka::JoysticManager::GetInstance()->GetContoroller(i).m_state.Gamepad.wButtons,
						oka::JoysticManager::GetInstance()->GetContoroller(i).m_downkey,
						oka::JoysticManager::GetInstance()->GetContoroller(i).m_sThumbLX,
						oka::JoysticManager::GetInstance()->GetContoroller(i).m_sThumbLY);*/

				}
				else
				{

					//g_useController[i]->control();

				}

			}


			//�S�I�u�W�F�N�g��Update
			for (unsigned int i = 0; i < oka::GameManager::GetInstance()->m_gameObject.size(); i++)
			{
				oka::GameManager::GetInstance()->m_gameObject[i]->Update();
			}



			/*for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++) 
			{
				oka::CharacterManager::GetInstance()->m_character[i]->Update();
			}*/

			//�ڐG����
			for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++) {
				for (unsigned int t = i + 1; t < CharacterManager::GetInstance()->GetCharacterNumber(); t++) {

					//�O�ւƑO��
					if (isHitCharacter(oka::CharacterManager::GetInstance()->m_character[i]->m_frontPosition, oka::CharacterManager::GetInstance()->m_character[t]->m_frontPosition) ||

						//�O�ւƌ��
						isHitCharacter(oka::CharacterManager::GetInstance()->m_character[i]->m_frontPosition, oka::CharacterManager::GetInstance()->m_character[t]->m_backPosition) ||

						//��ւƑO��
						isHitCharacter(oka::CharacterManager::GetInstance()->m_character[i]->m_backPosition, oka::CharacterManager::GetInstance()->m_character[t]->m_frontPosition) ||

						//��ւƌ��
						isHitCharacter(oka::CharacterManager::GetInstance()->m_character[i]->m_frontPosition, oka::CharacterManager::GetInstance()->m_character[t]->m_frontPosition)) {

						//1�t���[���O�̍��W�ɖ߂��Đi�s�����Ƃ�
						//�t�̃x�N�g���𑫂�����
						oka::Vec3 reverse = oka::CharacterManager::GetInstance()->m_character[i]->m_transform.GetPosition() - oka::CharacterManager::GetInstance()->m_character[t]->m_transform.GetPosition();
						oka::CharacterManager::GetInstance()->m_character[i]->m_speed += reverse*0.01f;
						oka::CharacterManager::GetInstance()->m_character[t]->m_speed -= reverse*0.01f;
					}
				}
			}

		}


		//�G�t�F�N�g�̍X�V
		std::list<Effect*>::iterator it = effect.begin();
		it = effect.begin();
		while (it != effect.end())
		{
			(*it)->Update();
			(*it)->checkCourseOut();
			++it;
		}

		//�G�t�F�N�g�폜����
		it = effect.begin();
		while (it != effect.end()) {

			if (false == (*it)->m_isActive) {
				it = effect.erase(it);
				continue;
			}

			it++;

		}


		//-------------------------------------
		//�`��(3D)

		if (SINGLE_MODE == modeCommand) {

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

			////����
			//glViewport(0, g_window_height / 2, g_window_width / 2, g_window_height / 2);
			//g_camera->SetPosition({
			//	player1->transform.m_position.m_x + sin(player1->transform.m_rotate.m_y) * 8,
			//	player1->transform.m_position.m_y + 3.5f,
			//	player1->transform.m_position.m_z + cos(player1->transform.m_rotate.m_y) * 8
			//});
			//g_camera->SetTarget({ player1->transform.m_position });
			//g_camera->update(TYPE_3D);

			//func(player1);

			////�E��
			//glViewport(g_window_width / 2, g_window_height / 2, g_window_width / 2, g_window_height / 2);
			//g_camera->SetPosition({
			//	player2->transform.m_position.m_x + sin(player2->transform.m_rotate.m_y) * 8,
			//	player2->transform.m_position.m_y + 3.5f,
			//	player2->transform.m_position.m_z + cos(player2->transform.m_rotate.m_y) * 8
			//});
			//g_camera->SetTarget({ player2->transform.m_position });
			//g_camera->update(TYPE_3D);

			//func(player2);

			////����
			//glViewport(0, 0, g_window_width / 2, g_window_height / 2);
			//g_camera->SetPosition({
			//	player3->transform.m_position.m_x + sin(player3->transform.m_rotate.m_y) * 8,
			//	player3->transform.m_position.m_y + 3.5f,
			//	player3->transform.m_position.m_z + cos(player3->transform.m_rotate.m_y) * 8
			//});
			//g_camera->SetTarget({ player3->transform.m_position });
			//g_camera->update(TYPE_3D);

			//func(player3);

			////�E��
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
			//�X�^�[�g�{�^���������ꂽ��
			//�^�C�g���V�[���Ɉڍs
			if (oka::JoysticManager::GetInstance()->GetContoroller(0).m_downkey & XINPUT_GAMEPAD_START)
			{
				GameManager::GetInstance()->_sequence.change(&GameManager::sceneTitle);

				title_pushAnyKey = false;
				g_isCourseDecision = false;
				modeCommand = SINGLE_MODE;

				//�R�[�Xbgm��~
				//course->m_bgm->stop();

				//�G���W�������~�߂�
				//player1->m_engine->stop();

				//���[�v�ɕK�v�ȏ���������
				startRace = false;
				startFrame = 0;//�t���[����
				timenow = 0;//�o�ߎ���
				timebase = 0;//�v���J�n����
				startCount = 6;

				//���񐔕\���N���A
				memset(str_lapMax, 0, sizeof(str_lapMax));

				//�L�����N�^�[�폜
				/*for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++) {

					delete character[i];

				}
				character.clear();*/

				//�G�t�F�N�g�폜
				effect.clear();

			}

		}
	}

}