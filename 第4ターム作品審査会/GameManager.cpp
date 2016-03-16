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
void GameManager::updata() {

	m_flame++;
	_sequence.run(this, 1.0f / 60.0f);

}


//��芸����
//�R�[�X�I�����

GLuint threeTexture = 0;
GLuint twoTexture = 0;

GLuint oneTexture = 0;
GLuint goTexture = 0;
GLuint goalTexture = 0;

GLuint rank1st = 0;
GLuint rank2nd = 0;
GLuint rank3rd = 0;
GLuint rank4th = 0;



//��芸����
int startFrame = 0;//�t���[����
int timenow = 0;//�o�ߎ���
int timebase = 0;//�v���J�n����
int startCount = 6;

//���񐔕\���Ɏg��
char str_lapMax[256];

int getMilliSecond(int _flame){
	return ((_flame * 1000) / 60) % 1000;
}

int getSecond(int _flame){
	return _flame / 60;
}

int getMinute(int _second){
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
bool checkRanking(Character *_character1, Character *_character2){

	//���񐔂ł̔���
	if (_character1->m_lapCount > _character2->m_lapCount){
		return true;
	}
	else if (_character1->m_lapCount < _character2->m_lapCount){
		return false;
	}

	//�`�F�b�N�|�C���g�̐i�݋�ł̔���
	if (_character1->m_nowPoint > _character2->m_nowPoint){
		return true;
	}
	else if (_character1->m_nowPoint < _character2->m_nowPoint){
		//return true;
		return false;
	}

	//�ڎw���Ă���`�F�b�N�|�C���g�ւ̋����ł̔���
	if (_character1->m_nextCheckPointLength > _character2->m_nextCheckPointLength){
		return false;
	}
	else if (_character1->m_nextCheckPointLength < _character2->m_nextCheckPointLength){
		return true;
	}

	//��芸���������Ԃ�
	return false;

}


//-------------------------------------
//���[�X�X�^�[�g�̃J�E���g�_�E��
void countRaceStart(){

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
	if (3 == startCount && startFrame == 0){
		startCountDown->play();
	}
	if (3 == startCount && startFrame == 30){
		startCountDown->stop();
	}

	if (2 == startCount && startFrame == 0){
		startCountDown->play();
	}
	if (2 == startCount && startFrame == 30){
		startCountDown->stop();
	}

	if (1 == startCount && startFrame == 0){
		startCountDown->play();
	}
	if (1 == startCount && startFrame == 30){
		startCountDown->stop();

		alSourcef(startCountDown->m_sid, AL_PITCH, 2);

	}

	if (0 == startCount && startFrame == 0){
		startCountDown->play();
	}

	if (-1 == startCount && startFrame == 10){
		startCountDown->stop();
		course->m_bgm->play();
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

void init(){

	srand(time(NULL));

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
	threeTexture = BmpImage::loadImage_alpha("bmp/start/three.bmp");
	twoTexture = BmpImage::loadImage_alpha("bmp/start/two.bmp");
	oneTexture = BmpImage::loadImage_alpha("bmp/start/one.bmp");
	goTexture = BmpImage::loadImage_alpha("bmp/start/go.bmp");
	goalTexture = BmpImage::loadImage_alpha("bmp/goal.bmp");

	smoke_handle = BmpImage::loadImage_alpha("bmp/Effect/smoke.bmp");
	dash_handle = BmpImage::loadImage_alpha("bmp/Effect/dash.bmp");

	rank1st = BmpImage::loadImage_alpha("bmp/Ranking/1st.bmp");
	rank2nd = BmpImage::loadImage_alpha("bmp/Ranking/2nd.bmp");
	rank3rd = BmpImage::loadImage_alpha("bmp/Ranking/3rd.bmp");
	rank4th = BmpImage::loadImage_alpha("bmp/Ranking/4th.bmp");

	dashIcon = BmpImage::loadImage_alpha("bmp/dashIcon.bmp");
	dashGauge = BmpImage::loadImage_alpha("bmp/gauge.bmp");

	EffectBlizzard = BmpImage::loadImage_alpha("bmp/Effect/blizzard.bmp");

	//�g�p���閂�΂̃e�N�X�`���ǂݍ���
	ItemFire = BmpImage::loadImage("bmp/MagicStone/ms_fire.bmp");
	ItemBlizzard = BmpImage::loadImage("bmp/MagicStone/ms_blizzard.bmp");

	//�g�p���鉹�ǂݍ���	
	SoundManager::getInstance()->addSound("pushStartButtonSE", new Sound("wav/pushStartButton.wav"));
	SoundManager::getInstance()->addSound("TitleBGM", new Sound("wav/titleBGM.wav"));	
	SoundManager::getInstance()->addSound("cursorMoveSE", new Sound("wav/cursorMove.wav"));
	SoundManager::getInstance()->addSound("modeDecision", new Sound("wav/modeDecision.wav"));
	SoundManager::getInstance()->addSound("courseDecision", new Sound("wav/courseDecision.wav"));
	SoundManager::getInstance()->addSound("slipSE", new Sound("wav/slip.wav"));	
	SoundManager::getInstance()->addSound("fireSE", new Sound("wav/fire.wav"));
	SoundManager::getInstance()->addSound("chargeComplete", new Sound("wav/chargeComplete.wav"));
	SoundManager::getInstance()->addSound("getItem", new Sound("wav/getItem.wav"));
	SoundManager::getInstance()->addSound("lapCountSE", new Sound("wav/lapCount.wav"));
	SoundManager::getInstance()->addSound("finalLapSE", new Sound("wav/finalLap.wav"));
	SoundManager::getInstance()->addSound("goalSE", new Sound("wav/goal.wav"));

	startCountDown = new Sound();
	startCountDown->loadKukeiha(count_sound, sizeof(count_sound), 440);


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

void GameManager::sceneTitle(float delta) {

	if (0.0f == _sequence.getTime()){

		printf("�^�C�g���V�[��������������܂���\n");
		printf("\n");

		init();//�Q�[���̏�����

		title = new Moji(250.f, 250.f, { 20.f, 50.f }, { 1, 1, 1 }, "bmp/title/title.bmp");

		SoundManager::getInstance()->m_sounds["TitleBGM"]->play();

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

	glLineWidth(5);
	StrokeString::print("Bike", { 105, 180, 0 }, 0.3f, { 1, 1, 1 });
	StrokeString::print("Racing", { 85, 135, 0 }, 0.3f, { 1, 1, 1 });


	//�V�[���̑J��
	if (false == title_pushAnyKey && JoysticManager::getInstance()->m_contoroller[0].m_downkey & XINPUT_GAMEPAD_START){

		title_pushAnyKey = true;
		SoundManager::getInstance()->m_sounds["pushStartButtonSE"]->play();

	}

	if (false == title_pushAnyKey){

		if ((GameManager::m_flame % 60) < 30){
			glLineWidth(4);
			StrokeString::print("PUSH START BUTTON", { 75, 40, 0 }, 0.1f, { 1, 1, 1 });
		}

	}
	else{

		if (JoysticManager::getInstance()->m_contoroller[0].m_yTopDown){

			modeCommand++;
			modeCommand = (modeCommand + TITLE_MAX) % TITLE_MAX;
			SoundManager::getInstance()->m_sounds["cursorMoveSE"]->play();

		}

		if (JoysticManager::getInstance()->m_contoroller[0].m_yBottomDown){

			modeCommand--;
			modeCommand = (modeCommand + TITLE_MAX) % TITLE_MAX;
			SoundManager::getInstance()->m_sounds["cursorMoveSE"]->play();

		}


		if (JoysticManager::getInstance()->m_contoroller[0].m_downkey & XINPUT_GAMEPAD_A){

			if (SINGLE_MODE == modeCommand){
				g_useController[0]->m_type = PLAYER;
			}

			else if (VS_MODE == modeCommand){

				for (int i = 0; i < JoysticManager::getInstance()->connectingNum(); i++){
					g_useController[i]->m_type = PLAYER;
				}

			}

			GameManager::getInstance()->_sequence.change(&GameManager::sceneCourseSelect);
			SoundManager::getInstance()->m_sounds["modeDecision"]->play();
		}

		glLineWidth(4);
		if (SINGLE_MODE == modeCommand){
			StrokeString::print("SINGLE MODE", { 100, 55, 0 }, 0.1f, { 1, 0, 0 });
		}
		else{
			StrokeString::print("SINGLE MODE", { 100, 55, 0 }, 0.1f, { 1, 1, 1 });
		}

		if (VS_MODE == modeCommand){
			StrokeString::print("VS MODE", { 115, 25, 0 }, 0.1f, { 1, 0, 0 });
		}
		else{
			StrokeString::print("VS MODE", { 115, 25, 0 }, 0.1f, { 1, 1, 1 });
		}

		glLineWidth(1);
		StrokeString::print("[Lstick]CourseSelect", { 200, 5, 0 }, 0.05f, { 1, 1, 1 });
		StrokeString::print("[A]Accept", { 260, 5, 0 }, 0.05f, { 1, 1, 1 });

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
	if (false == g_isCourseDecision){
		glLineWidth(1);
		StrokeString::print("[Lstick]CourseSelect", { 200, 5, 0 }, 0.05f, { 1, 1, 1 });
		StrokeString::print("[A]Accept", { 260, 5, 0 }, 0.05f, { 1, 1, 1 });
	}

	if (false == g_isCourseDecision && JoysticManager::getInstance()->m_contoroller[0].m_xRightDown){
	
		selectedCourse++;
		selectedCourse = (selectedCourse + COURSE_NUM_MAX) % COURSE_NUM_MAX;
		SoundManager::getInstance()->m_sounds["cursorMoveSE"]->play();
	
	}

	if (false == g_isCourseDecision && JoysticManager::getInstance()->m_contoroller[0].m_xLeftDown){
		
		selectedCourse--;
		selectedCourse = (selectedCourse + COURSE_NUM_MAX) % COURSE_NUM_MAX;
		SoundManager::getInstance()->m_sounds["cursorMoveSE"]->play();

	}

	if (false == g_isCourseDecision && JoysticManager::getInstance()->m_contoroller[0].m_downkey & XINPUT_GAMEPAD_A){

		g_isCourseDecision = true;
		
		SoundManager::getInstance()->m_sounds["TitleBGM"]->stop();
					
		SoundManager::getInstance()->m_sounds["courseDecision"]->play();

		//�A�C�e���������R�[�X�̐������A�C�e���̐ݒu
		//�A�C�e���̐���
		for (int i = 0; i < SET_ITEM_NUMBER; i++){
			item[i] = new Item();
		}

		//�R�[�X�̐���
		course = createCourse();

		//�v���C���[�̏������W����
		if (COURSE1 == selectedCourse){
			course->m_bgm = new Sound();
			course->m_bgm->loadWavFile("wav/course1BGM.wav");
			course->m_bgm->changeVolume(0.5f);

			player1->m_transform.SetPosition(oka::Vec3(14.f, 0.0f, -165.f));
			player2->m_transform.SetPosition(oka::Vec3(18.f, 0.f, -160.f));
			player3->m_transform.SetPosition(oka::Vec3(22.f, 0.f, -155.f));
			player4->m_transform.SetPosition(oka::Vec3(26.f, 0.f, -150.f));
		}
		else if (COURSE2 == selectedCourse){
			course->m_bgm = new Sound();
			course->m_bgm->loadWavFile("wav/course2BGM.wav");
			course->m_bgm->changeVolume(0.6f);

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
void GameManager::scenePlay(float delta) {

	if (0.0f == _sequence.getTime()){

		printf("�v���C�V�[��������������܂���\n");
		printf("\n");

		//delete titleBGM;
		//delete cursorMove_SE;

		sprintf_s(str_lapMax, "%d", 3);

		//�v���C���[�̃G���W����
		player1->m_engine->play();


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

	if (true == (character[0]->m_isGoal && character[1]->m_isGoal && character[2]->m_isGoal && character[3]->m_isGoal)){

		//�X�^�[�g�{�^���������ꂽ��
		//�^�C�g���V�[���Ɉڍs
		if (JoysticManager::getInstance()->m_contoroller[0].m_downkey & XINPUT_GAMEPAD_START){
			GameManager::getInstance()->_sequence.change(&GameManager::sceneTitle);

			title_pushAnyKey = false;
			g_isCourseDecision = false;
			modeCommand = SINGLE_MODE;

			//�R�[�Xbgm��~
			course->m_bgm->stop();

			//�G���W�������~�߂�
			player1->m_engine->stop();

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