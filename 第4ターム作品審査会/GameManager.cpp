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

//レースが始まっているかのフラグ
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


//取り敢えず
//コース選択画面

GLuint threeTexture = 0;
GLuint twoTexture = 0;

GLuint oneTexture = 0;
GLuint goTexture = 0;
GLuint goalTexture = 0;

GLuint rank1st = 0;
GLuint rank2nd = 0;
GLuint rank3rd = 0;
GLuint rank4th = 0;



//取り敢えず
int startFrame = 0;//フレーム数
int timenow = 0;//経過時間
int timebase = 0;//計測開始時間
int startCount = 6;

//周回数表示に使う
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


//接触判定
//取り敢えず
bool isHitCharacter(oka::Vec3 _myPos, oka::Vec3 _youPos){

	oka::Vec3 v = _myPos - _youPos;

	float hitLine = 2.4f;

	if (v.length() < hitLine){
		return true;
	}

	return false;

}

//順位判定用の関数
//順位の判定のみする
bool checkRanking(Character *_character1, Character *_character2){

	//周回数での判定
	if (_character1->m_lapCount > _character2->m_lapCount){
		return true;
	}
	else if (_character1->m_lapCount < _character2->m_lapCount){
		return false;
	}

	//チェックポイントの進み具合での判定
	if (_character1->m_nowPoint > _character2->m_nowPoint){
		return true;
	}
	else if (_character1->m_nowPoint < _character2->m_nowPoint){
		//return true;
		return false;
	}

	//目指しているチェックポイントへの距離での判定
	if (_character1->m_nextCheckPointLength > _character2->m_nextCheckPointLength){
		return false;
	}
	else if (_character1->m_nextCheckPointLength < _character2->m_nextCheckPointLength){
		return true;
	}

	//取り敢えず何か返す
	return false;

}


//-------------------------------------
//レーススタートのカウントダウン
void countRaceStart(){

	startFrame++; //フレーム数を＋１

	timenow = glutGet(GLUT_ELAPSED_TIME);//経過時間を取得

	if (timenow - timebase > 1000)      //１秒以上たったら処理を行う
	{
		startCount--;

		if (0 == startCount){

			//カウントダウンが終了したら
			//レースが開始されているかのフラグを立てる
			startRace = true;

		}

		timebase = timenow;//基準時間を設定                
		startFrame = 0;//フレーム数をリセット
	}

	//カウントダウンの音
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
//ゲームの初期化全般を行う

void init(){

	srand(time(NULL));

	//後で書き換え
	//xFile rider;
	xFile body;
	xFile backWheel;

	//モデルデータの読み込み
	//xFile::loadXfile("xFile/player.x", rider);
	xFile::loadXfile("xFile/bike.x", body);
	xFile::loadXfile("xFile/taiya.x", backWheel);

	//車体のモデルデータの向き修正
	body.rotate();

	//後で書き換え
	//プレイヤーの生成
	player1 = new Character();
	player1->m_kind = PLAYER0;
	player1->m_body = body;
	player1->m_backWheel = backWheel;

	//敵の生成
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

	//生成したプレイヤーと敵をベクターで管理
	character.push_back(player1);
	character.push_back(player2);
	character.push_back(player3);
	character.push_back(player4);

	//使用するコントローラーの対応付け
	g_useController.push_back(player1);
	g_useController.push_back(player2);
	g_useController.push_back(player3);
	g_useController.push_back(player4);

	//カメラの生成
	g_camera = new oka::Camera();

	//テクスチャの読み込み
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

	//使用する魔石のテクスチャ読み込み
	ItemFire = BmpImage::loadImage("bmp/MagicStone/ms_fire.bmp");
	ItemBlizzard = BmpImage::loadImage("bmp/MagicStone/ms_blizzard.bmp");

	//使用する音読み込み	
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


	//最初の順位設定と順位付与
	for (unsigned int i = 0; i < character.size(); i++){
		std::sort(character.begin(), character.end(), checkRanking);
	}

	for (unsigned int i = 0; i < character.size(); i++){
		character[i]->m_ranking = i + 1;
	}
}


//-------------------------------------------------------------------------------------------------------
//タイトル処理

enum{
	SINGLE_MODE = 0,
	VS_MODE,
	TITLE_MAX
};


bool title_pushAnyKey = false;
int modeCommand = SINGLE_MODE;

void GameManager::sceneTitle(float delta) {

	if (0.0f == _sequence.getTime()){

		printf("タイトルシーンが初期化されました\n");
		printf("\n");

		init();//ゲームの初期化

		title = new Moji(250.f, 250.f, { 20.f, 50.f }, { 1, 1, 1 }, "bmp/title/title.bmp");

		SoundManager::getInstance()->m_sounds["TitleBGM"]->play();

	}

	glViewport(0, 0, g_window_width, g_window_height);

	//更新
	g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);

	//描画
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	title->draw();

	if (GameManager::m_flame % 60){
		title->changeColor();
	}

	glLineWidth(5);
	StrokeString::print("Bike", { 105, 180, 0 }, 0.3f, { 1, 1, 1 });
	StrokeString::print("Racing", { 85, 135, 0 }, 0.3f, { 1, 1, 1 });


	//シーンの遷移
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
//コース選択処理
//RB LBでコースの選択をしてAでコース決定

bool g_isCourseDecision = false;

void GameManager::sceneCourseSelect(float delta) {

	if (0.0f == _sequence.getTime()){
		printf("コースセレクトシーンが初期化されました\n");
		printf("\n");

		//アイテムの添え字初期化
		itemNum = 0;

		courseSelectBG = new Moji(300.f, 300.f, { 0.f, 0.f }, { 1, 1, 1 }, "bmp/courseSelect/courseSelectBG.bmp");
		courseSelect = new Moji(280.f, 70.f, { 18.f, 230.f }, {0.f,1.f,0.f}, "bmp/courseSelect/courseSelect.bmp");
		course1_map = new Moji(240.f, 240.f, { 50.f, 10.f }, { 1, 1, 1 }, "bmp/courseSelect/course1_map.bmp");
		course2_map = new Moji(230.f, 200.f, { 55.f, 30.f }, { 1, 1, 1 }, "bmp/courseSelect/course2_map.bmp");


	}

	glViewport(0, 0, g_window_width, g_window_height);

	//更新
	g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);

	//描画
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	if (g_isCourseDecision){
		courseSelectBG->fadeOut();
		courseSelect->fadeOut();
		course1_map->fadeOut();
		course2_map->fadeOut();
	}

	//コースセレクト
	courseSelectBG->draw();
	courseSelect->draw();

	if (COURSE1 == selectedCourse){

		//コースの様子
		course1_map->draw();


	}
	else if (COURSE2 == selectedCourse){

		course2_map->draw();

	}

	//操作方法
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

		//アイテム生成→コースの生成→アイテムの設置
		//アイテムの生成
		for (int i = 0; i < SET_ITEM_NUMBER; i++){
			item[i] = new Item();
		}

		//コースの生成
		course = createCourse();

		//プレイヤーの初期座標決定
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

	//プレイシーンに移行
	if (g_isCourseDecision && 0.f >= courseSelectBG->m_alpha){

		GameManager::getInstance()->_sequence.change(&GameManager::scenePlay);

	}


	glFlush();

}



/////////////

void func(Character *_pCharacter){

	//深度テスト
	glEnable(GL_DEPTH_TEST);

	//ライト
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

	//車体部と車輪部のみライティングを有効にしてある
	//影部はライティング無効
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

	//煙の描画
	for (unsigned int i = 0; i < character.size(); i++){

		character[i]->m_smoke.draw();

	}

	//エフェクトの描画
	auto it = effect.begin();
	while (it != effect.end())
	{
		(*it)->draw();
		++it;
	}

	/*更新*/
	g_camera->Ortho(0.0f, 300.f, 0.0f, 300.f, 1.0f, -1.0f);

	countRaceStart();
	printRaceStart();

	/*描画(2D)*/

	//順位の表示
	_pCharacter->printRanking();
	_pCharacter->printStatus();


}

//-------------------------------------------------------------------------------------------------------
void GameManager::scenePlay(float delta) {

	if (0.0f == _sequence.getTime()){

		printf("プレイシーンが初期化されました\n");
		printf("\n");

		//delete titleBGM;
		//delete cursorMove_SE;

		sprintf_s(str_lapMax, "%d", 3);

		//プレイヤーのエンジン音
		player1->m_engine->play();


	}



	//-------------------------------------
	//更新

	//レースが始まったらする処理
	if (true == startRace){

		//順位の判定
		for (unsigned int i = 0; i < character.size(); i++){
			std::sort(character.begin(), character.end(), checkRanking);
		}

		//順位の設定
		//実際に順位を付与する処理
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

		//接触判定
		for (unsigned int i = 0; i < character.size(); i++){
			for (unsigned int t = i + 1; t < character.size(); t++){

				//前輪と前輪
				if (isHitCharacter(character[i]->m_frontPosition, character[t]->m_frontPosition) ||

					//前輪と後輪
					isHitCharacter(character[i]->m_frontPosition, character[t]->m_backPosition) ||

					//後輪と前輪
					isHitCharacter(character[i]->m_backPosition, character[t]->m_frontPosition) ||

					//後輪と後輪
					isHitCharacter(character[i]->m_frontPosition, character[t]->m_frontPosition)){

					//1フレーム前の座標に戻して進行方向とは
					//逆のベクトルを足し込む
					oka::Vec3 reverse = character[i]->m_transform.GetPosition() - character[t]->m_transform.GetPosition();
					character[i]->m_speed += reverse*0.01f;
					character[t]->m_speed -= reverse*0.01f;
				}
			}
		}

	}

	//アイテムの更新
	for (int i = 0; i < SET_ITEM_NUMBER; i++){
		item[i]->update();
	}


	//エフェクトの更新
	std::list<Effect*>::iterator it = effect.begin();
	it = effect.begin();
	while (it != effect.end())
	{
		(*it)->update();
		(*it)->checkCourseOut();
		++it;
	}

	//エフェクト削除処理
	it = effect.begin();
	while (it != effect.end()){

		if (false == (*it)->m_isActive){
			it = effect.erase(it);
			continue;
		}

		it++;

	}


	//-------------------------------------
	//描画(3D)

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

	if (true == (character[0]->m_isGoal && character[1]->m_isGoal && character[2]->m_isGoal && character[3]->m_isGoal)){

		//スタートボタンが押されたら
		//タイトルシーンに移行
		if (JoysticManager::getInstance()->m_contoroller[0].m_downkey & XINPUT_GAMEPAD_START){
			GameManager::getInstance()->_sequence.change(&GameManager::sceneTitle);

			title_pushAnyKey = false;
			g_isCourseDecision = false;
			modeCommand = SINGLE_MODE;

			//コースbgm停止
			course->m_bgm->stop();

			//エンジン音を止める
			player1->m_engine->stop();

			//ループに必要な初期化処理
			startRace = false;
			startFrame = 0;//フレーム数
			timenow = 0;//経過時間
			timebase = 0;//計測開始時間
			startCount = 6;

			//周回数表示クリア
			memset(str_lapMax, 0, sizeof(str_lapMax));

			//キャラクター削除
			for (unsigned int i = 0; i < character.size(); i++){

				delete character[i];

			}
			character.clear();

			g_useController.clear();

			//エフェクト削除
			effect.clear();

		}

	}
}