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
#include"joysticManager.h"
#include"ImageManager.h"
#include"SoundManager.h"
#include"Sound.h"
#include"glut.h"


//debug
extern int g_window_width;
extern int g_window_height;

//���[�X���n�܂��Ă��邩�̃t���O
bool startRace = false;

GameManager* GameManager::m_instance = nullptr;

//-------------------------------------------------------------------------------------------------------
GameManager* GameManager::getInstance() {

	if (nullptr == m_instance) {
		m_instance = new GameManager();
	}
	return m_instance;
}


//-------------------------------------------------------------------------------------------------------

void GameManager::updata() 
{

	m_flame++;
	_sequence.run(this, 1.0f / 60.0f);

}


//��芸����
//�R�[�X�I�����

unsigned int threeTexture = 0;
unsigned int twoTexture = 0;

unsigned int oneTexture = 0;
unsigned int goTexture = 0;
unsigned int goalTexture = 0;

unsigned int rank1st = 0;
unsigned int rank2nd = 0;
unsigned int rank3rd = 0;
unsigned int rank4th = 0;



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


//�ڐG����
//��芸����
bool isHitCharacter(oka::Vec3 _myPos, oka::Vec3 _youPos){

	oka::Vec3 v = _myPos - _youPos;

	float hitLine = 2.4f;

	if (v.length() < hitLine){
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

		if (0 == startCount){

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
		oka::SoundManager::getInstance()->Play("CountDown");
	}
	if (3 == startCount && startFrame == 30)
	{
		oka::SoundManager::getInstance()->Stop("CountDown");
	}

	if (2 == startCount && startFrame == 0)
	{
		oka::SoundManager::getInstance()->Play("CountDown");
	}
	if (2 == startCount && startFrame == 30)
	{
		oka::SoundManager::getInstance()->Stop("CountDown");
	}

	if (1 == startCount && startFrame == 0)
	{
		oka::SoundManager::getInstance()->Play("CountDown");
	}
	if (1 == startCount && startFrame == 30)
	{
		oka::SoundManager::getInstance()->Stop("CountDown");
	}

	if (0 == startCount && startFrame == 0)
	{
		oka::SoundManager::getInstance()->ChangePitch("CountDown", 2.0f);
		oka::SoundManager::getInstance()->Play("CountDown");
	}

	if (-1 == startCount && startFrame == 10)
	{
		oka::SoundManager::getInstance()->Stop("CountDown");
		//course->m_bgm->play();
	}


}

void printRaceStart(){

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (startCount <= 3 && startCount > 0){
		glPushMatrix();
		{
			glTranslatef(100, 100, 0);

			if (startCount == 3){
				glBindTexture(GL_TEXTURE_2D, threeTexture);

			}
			else if (startCount == 2){
				glBindTexture(GL_TEXTURE_2D, twoTexture);
			}
			else if (startCount == 1){
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
	else if (0 == startCount){

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
	//��ŏ�������
	//xFile rider;
	xFile body;
	xFile backWheel;

	//���f���f�[�^�̓ǂݍ���
	//xFile::loadXfile("xFile/player.x", rider);
	xFile::loadXfile("xFile/bike.x", body);
	xFile::loadXfile("xFile/taiya.x", backWheel);

	//�ԑ̂̃��f���f�[�^�̌����C��
	body.rotate();

	//��ŏ�������
	//�v���C���[�̐���
	player1 = new Character();
	player1->m_kind = PLAYER0;
	player1->m_body = body;
	player1->m_backWheel = backWheel;

	//�G�̐���
	player2 = new Character();
	player2->m_kind = PLAYER1;
	player2->m_body = body;
	player2->m_backWheel = backWheel;

	player3 = new Character();
	player3->m_kind = PLAYER2;
	player3->m_body = body;
	player3->m_backWheel = backWheel;

	player4 = new Character();
	player4->m_kind = PLAYER3;
	player4->m_body = body;
	player4->m_backWheel = backWheel;

	//���������v���C���[�ƓG���x�N�^�[�ŊǗ�
	character.push_back(player1);
	character.push_back(player2);
	character.push_back(player3);
	character.push_back(player4);

	//�g�p����R���g���[���[�̑Ή��t��
	g_useController.push_back(player1);
	g_useController.push_back(player2);
	g_useController.push_back(player3);
	g_useController.push_back(player4);

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
	oka::SoundManager::getInstance()->AddSound("pushStartButtonSE",oka::Sound::LoadWavFile("wav/pushStartButton.wav"));
	oka::SoundManager::getInstance()->AddSound("TitleBGM", oka::Sound::LoadWavFile("wav/titleBGM.wav"));
	oka::SoundManager::getInstance()->AddSound("cursorMoveSE", oka::Sound::LoadWavFile("wav/cursorMove.wav"));
	oka::SoundManager::getInstance()->AddSound("modeDecision", oka::Sound::LoadWavFile("wav/modeDecision.wav"));
	oka::SoundManager::getInstance()->AddSound("courseDecision", oka::Sound::LoadWavFile("wav/courseDecision.wav"));
	oka::SoundManager::getInstance()->AddSound("slipSE", oka::Sound::LoadWavFile("wav/slip.wav"));
	oka::SoundManager::getInstance()->AddSound("fireSE", oka::Sound::LoadWavFile("wav/fire.wav"));
	oka::SoundManager::getInstance()->AddSound("chargeComplete", oka::Sound::LoadWavFile("wav/chargeComplete.wav"));
	oka::SoundManager::getInstance()->AddSound("getItem", oka::Sound::LoadWavFile("wav/getItem.wav"));
	oka::SoundManager::getInstance()->AddSound("lapCountSE", oka::Sound::LoadWavFile("wav/lapCount.wav"));
	oka::SoundManager::getInstance()->AddSound("finalLapSE", oka::Sound::LoadWavFile("wav/finalLap.wav"));
	oka::SoundManager::getInstance()->AddSound("goalSE", oka::Sound::LoadWavFile("wav/goal.wav"));

	oka::SoundManager::getInstance()->AddSound("CountDown", oka::Sound::LoadSquareWave(count_sound, sizeof(count_sound), 440));


	//�ŏ��̏��ʐݒ�Ə��ʕt�^
	for (unsigned int i = 0; i < character.size(); i++){
		std::sort(character.begin(), character.end(), checkRanking);
	}

	for (unsigned int i = 0; i < character.size(); i++){
		character[i]->m_ranking = i + 1;
	}
}


//-------------------------------------------------------------------------------------------------------
//�^�C�g������

enum{
	SINGLE_MODE = 0,
	VS_MODE,
	TITLE_MAX
};


bool title_pushAnyKey = false;
int modeCommand = SINGLE_MODE;

void GameManager::sceneTitle(float delta) 
{

	if (0.0f == _sequence.getTime()){

		printf("�^�C�g���V�[��������������܂���\n");
		printf("\n");

		init();//�Q�[���̏�����

		title = new Moji(250.f, 250.f, { 20.f, 50.f }, { 1, 1, 1 }, "bmp/title/title.bmp");

		oka::SoundManager::getInstance()->Play("TitleBGM");

	}

	glViewport(0, 0, g_window_width, g_window_height);

	//�X�V
	g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);

	//�`��
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	title->draw();

	if (GameManager::m_flame % 60){
		title->changeColor();
	}

	oka::SetLineWidth(5.0f);
	oka::DrawString("Bike", 105.0f, 180.0f, 0.3f);
	oka::DrawString("Racing", 85.0f, 135.0f, 0.3f);

	//�V�[���̑J��
	if (false == title_pushAnyKey && JoysticManager::getInstance()->m_contoroller[0].m_downkey & XINPUT_GAMEPAD_START){

		title_pushAnyKey = true;
		oka::SoundManager::getInstance()->Play("pushStartButtonSE");

	}

	if (false == title_pushAnyKey){

		if ((GameManager::m_flame % 60) < 30)
		{
			oka::SetLineWidth(4.0f);
			oka::DrawString("PUSH START BUTTON", 75.0f, 40.0f, 0.1f);
		}

	}
	else
	{
		if (JoysticManager::getInstance()->m_contoroller[0].m_yTopDown)
		{
			modeCommand++;
			modeCommand = (modeCommand + TITLE_MAX) % TITLE_MAX;
			oka::SoundManager::getInstance()->Play("cursorMoveSE");

		}

		if (JoysticManager::getInstance()->m_contoroller[0].m_yBottomDown)
		{
			modeCommand--;
			modeCommand = (modeCommand + TITLE_MAX) % TITLE_MAX;
			oka::SoundManager::getInstance()->Play("cursorMoveSE");

		}


		if (JoysticManager::getInstance()->m_contoroller[0].m_downkey & XINPUT_GAMEPAD_A)
		{
			if (SINGLE_MODE == modeCommand){
				g_useController[0]->m_type = PLAYER;
			}

			else if (VS_MODE == modeCommand)
			{
				for (int i = 0; i < JoysticManager::getInstance()->connectingNum(); i++)
				{
					g_useController[i]->m_type = PLAYER;
				}

			}

			GameManager::getInstance()->_sequence.change(&GameManager::sceneCourseSelect);
			oka::SoundManager::getInstance()->Play("modeDecision");
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

	if (0.0f == _sequence.getTime()){
		printf("�R�[�X�Z���N�g�V�[��������������܂���\n");
		printf("\n");

		//�A�C�e���̓Y����������
		itemNum = 0;

		courseSelectBG = new Moji(300.f, 300.f, { 0.f, 0.f }, { 1, 1, 1 }, "bmp/courseSelect/courseSelectBG.bmp");
		courseSelect = new Moji(280.f, 70.f, { 18.f, 230.f }, {0.f,1.f,0.f}, "bmp/courseSelect/courseSelect.bmp");
		course1_map = new Moji(240.f, 240.f, { 50.f, 10.f }, { 1, 1, 1 }, "bmp/courseSelect/course1_map.bmp");
		course2_map = new Moji(230.f, 200.f, { 55.f, 30.f }, { 1, 1, 1 }, "bmp/courseSelect/course2_map.bmp");


	}

	glViewport(0, 0, g_window_width, g_window_height);

	//�X�V
	g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);

	//�`��
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	if (g_isCourseDecision){
		courseSelectBG->fadeOut();
		courseSelect->fadeOut();
		course1_map->fadeOut();
		course2_map->fadeOut();
	}

	//�R�[�X�Z���N�g
	courseSelectBG->draw();
	courseSelect->draw();

	if (COURSE1 == selectedCourse){

		//�R�[�X�̗l�q
		course1_map->draw();


	}
	else if (COURSE2 == selectedCourse){

		course2_map->draw();

	}

	//������@
	if (false == g_isCourseDecision)
	{
		oka::SetDefaultLineWidth();
		oka::DrawString("[Lstick]CourseSelect", 200.0f, 5.0f, 0.05f);
		oka::DrawString("[Lstick]CourseSelect", 260.0f, 5.0f, 0.05f);
	}

	if (false == g_isCourseDecision && JoysticManager::getInstance()->m_contoroller[0].m_xRightDown){
	
		selectedCourse++;
		selectedCourse = (selectedCourse + COURSE_NUM_MAX) % COURSE_NUM_MAX;
		oka::SoundManager::getInstance()->Play("cursorMoveSE");
	
	}

	if (false == g_isCourseDecision && JoysticManager::getInstance()->m_contoroller[0].m_xLeftDown){
		
		selectedCourse--;
		selectedCourse = (selectedCourse + COURSE_NUM_MAX) % COURSE_NUM_MAX;
		oka::SoundManager::getInstance()->Play("cursorMoveSE");

	}

	if (false == g_isCourseDecision && JoysticManager::getInstance()->m_contoroller[0].m_downkey & XINPUT_GAMEPAD_A){

		g_isCourseDecision = true;
		
		oka::SoundManager::getInstance()->Stop("TitleBGM");
		oka::SoundManager::getInstance()->Play("courseDecision");

		//�A�C�e���������R�[�X�̐������A�C�e���̐ݒu
		//�A�C�e���̐���
		for (int i = 0; i < SET_ITEM_NUMBER; i++){
			item[i] = new Item();
		}

		//�R�[�X�̐���
		course = createCourse();

		//�v���C���[�̏������W����
		if (COURSE1 == selectedCourse)
		{
			oka::SoundManager::getInstance()->AddSound("Course1Bgm", oka::Sound::LoadWavFile("wav/course1BGM.wav"));
			oka::SoundManager::getInstance()->ChangeVolume("Course1Bgm",0.5f);

			player1->m_transform.SetPosition(oka::Vec3(14.f, 0.0f, -165.f));
			player2->m_transform.SetPosition(oka::Vec3(18.f, 0.f, -160.f));
			player3->m_transform.SetPosition(oka::Vec3(22.f, 0.f, -155.f));
			player4->m_transform.SetPosition(oka::Vec3(26.f, 0.f, -150.f));
		}
		else if (COURSE2 == selectedCourse){
			oka::SoundManager::getInstance()->AddSound("Course2Bgm", oka::Sound::LoadWavFile("wav/course2BGM.wav"));
			oka::SoundManager::getInstance()->ChangeVolume("Course2Bgm", 0.5f);

			player1->m_transform.SetPosition(oka::Vec3(17.f, 0.f, -110.5f));
			player2->m_transform.SetPosition(oka::Vec3(25.f, 0.f, -105.5f));
			player3->m_transform.SetPosition(oka::Vec3(33.f, 0.f, -100.5f));
			player4->m_transform.SetPosition(oka::Vec3(41.f, 0.f, -95.5f));

		}

	}

	//�v���C�V�[���Ɉڍs
	if (g_isCourseDecision && 0.f >= courseSelectBG->m_alpha){

		GameManager::getInstance()->_sequence.change(&GameManager::scenePlay);

	}


	glFlush();

}



/////////////

void func(Character *_pCharacter){

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
	for (unsigned int i = 0; i < character.size(); i++){

		character[i]->draw();

	}

	for (int i = 0; i < SET_ITEM_NUMBER; i++){
		item[i]->draw();
	}

	for (unsigned int i = 0; i < character.size(); i++){

		character[i]->drawHasItem();

	}

	glDisable(GL_DEPTH_TEST);

	//���̕`��
	for (unsigned int i = 0; i < character.size(); i++){

		character[i]->m_smoke.draw();

	}

	//�G�t�F�N�g�̕`��
	auto it = effect.begin();
	while (it != effect.end())
	{
		(*it)->draw();
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
		oka::SoundManager::getInstance()->Play("Engine");

	}



	//-------------------------------------
	//�X�V

	//���[�X���n�܂����炷�鏈��
	if (true == startRace){

		//���ʂ̔���
		for (unsigned int i = 0; i < character.size(); i++){
			std::sort(character.begin(), character.end(), checkRanking);
		}

		//���ʂ̐ݒ�
		//���ۂɏ��ʂ�t�^���鏈��
		for (unsigned int i = 0; i < character.size(); i++){
			character[i]->m_ranking = i + 1;
		}

		for (unsigned int i = 0; i < g_useController.size(); i++){

			if (true == JoysticManager::getInstance()->m_contoroller[i].m_isConnect &&
				PLAYER == g_useController[i]->m_type){

				g_useController[i]->control(
					JoysticManager::getInstance()->m_contoroller[i].m_state.Gamepad.wButtons,
					JoysticManager::getInstance()->m_contoroller[i].m_downkey,
					JoysticManager::getInstance()->m_contoroller[i].m_sThumbLX,
					JoysticManager::getInstance()->m_contoroller[i].m_sThumbLY);

			}
			else{

				g_useController[i]->control();

			}

		}

		for (unsigned int i = 0; i < character.size(); i++){

			character[i]->update();

		}

		//�ڐG����
		for (unsigned int i = 0; i < character.size(); i++){
			for (unsigned int t = i + 1; t < character.size(); t++){

				//�O�ւƑO��
				if (isHitCharacter(character[i]->m_frontPosition, character[t]->m_frontPosition) ||

					//�O�ւƌ��
					isHitCharacter(character[i]->m_frontPosition, character[t]->m_backPosition) ||

					//��ւƑO��
					isHitCharacter(character[i]->m_backPosition, character[t]->m_frontPosition) ||

					//��ւƌ��
					isHitCharacter(character[i]->m_frontPosition, character[t]->m_frontPosition)){

					//1�t���[���O�̍��W�ɖ߂��Đi�s�����Ƃ�
					//�t�̃x�N�g���𑫂�����
					oka::Vec3 reverse = character[i]->m_transform.GetPosition() - character[t]->m_transform.GetPosition();
					character[i]->m_speed += reverse*0.01f;
					character[t]->m_speed -= reverse*0.01f;
				}
			}
		}

	}

	//�A�C�e���̍X�V
	for (int i = 0; i < SET_ITEM_NUMBER; i++){
		item[i]->update();
	}


	//�G�t�F�N�g�̍X�V
	std::list<Effect*>::iterator it = effect.begin();
	it = effect.begin();
	while (it != effect.end())
	{
		(*it)->update();
		(*it)->checkCourseOut();
		++it;
	}

	//�G�t�F�N�g�폜����
	it = effect.begin();
	while (it != effect.end()){

		if (false == (*it)->m_isActive){
			it = effect.erase(it);
			continue;
		}

		it++;

	}


	//-------------------------------------
	//�`��(3D)

	if (SINGLE_MODE == modeCommand){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glClearColor(77.f / 255.f, 180.f / 255.f, 232.f / 255.f, 1);

		oka::Vec3 pos;
		pos.m_x = player1->m_transform.GetPosition().m_x + sin(player1->m_transform.GetRotation().m_y) * 8;
		pos.m_y = player1->m_transform.GetPosition().m_y + 3.5f;
		pos.m_z = player1->m_transform.GetPosition().m_z + cos(player1->m_transform.GetRotation().m_y) * 8;
		
		oka::Vec3 target;
		target = player1->m_transform.GetPosition();

		oka::Vec3 up = oka::Vec3(0, 1, 0);

		g_camera->Perspective();
		g_camera->SetViewMatrix(pos, target, up);
		g_camera->MultViewMatrix();

		func(player1);

		glFlush();

	}

	else if (VS_MODE == modeCommand){

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

	if (true == (character[0]->m_isGoal && character[1]->m_isGoal && character[2]->m_isGoal && character[3]->m_isGoal))
	{
		//�X�^�[�g�{�^���������ꂽ��
		//�^�C�g���V�[���Ɉڍs
		if (JoysticManager::getInstance()->m_contoroller[0].m_downkey & XINPUT_GAMEPAD_START){
			GameManager::getInstance()->_sequence.change(&GameManager::sceneTitle);

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
			for (unsigned int i = 0; i < character.size(); i++){

				delete character[i];

			}
			character.clear();

			g_useController.clear();

			//�G�t�F�N�g�폜
			effect.clear();

		}

	}
}