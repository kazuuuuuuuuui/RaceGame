#pragma once

#include<vector>
#define _USE_MATH_DEFINES
#include<math.h>
#include"GameObject.h"
#include"Course.h"
#include"Smoke.h"
#include"Dash.h"
#include"xFile.h"

#define PLAYER_MAX_NUMBER (4)

//1周目 2周目 3周目
#define FIRST (0)
#define SECOND (1)
#define THIRD (2)

#define DASH_GAUGE_MAX (90)

extern char str_lapCount[256];

enum{
	PLAYER0,
	PLAYER1,
	PLAYER2,
	PLAYER3,
};

class Character :public GameObject{
public:

	Sound *m_engine;

	//自身の向きベクトル
	glm::vec2 OrientationVector;

	//自身の座標からAIポイントまでのベクトル
	glm::vec2 m_pos_to_AIpoint;

	//回転の際の補完値
	float CompletionValue;

	//種類
	int m_type;

	//自身の行列
	glm::mat4 m_matrix;

	//1フレーム前のポジション
	glm::vec3 m_lastPosition;

	//前輪と後輪のポジション
	glm::vec3 m_frontPosition;
	glm::vec3 m_backPosition;

	glm::vec3 m_dashSpeed;

	//アイテムに当たった時の回転値
	float m_crashRotate;

	//車輪の回転スピード
	float m_wheelSpeed;

	//人部分
	//xFile m_rider;

	//車体部分
	xFile m_body;

	//後輪部分
	xFile m_backWheel;

	//車体から出る煙
	Smoke m_smoke;

	//ダッシュ状態かどうかのフラグ
	bool m_isDash;

	//ダッシュに必要な力
	//約15秒に1回使えるように溜まっていく
	float m_dashPower;

	//ダッシュパワーが溜まった際にtrueになる
	bool m_isCharged;

	//ダッシュ時のエフェクト
	Dash *m_dash;

	//ラップタイム
	int m_flame;
	int m_milliSecond[LAP_MAX];
	int m_second[LAP_MAX];
	int m_minute[LAP_MAX];
	char m_str_lapTime[LAP_MAX][256];

	//周回数
	//正規の走法でコースを1周したら+1する
	int m_lapCount;

	//順位
	int m_ranking;

	//既定の周回数に達したらtrueになる
	bool m_isGoal;


	//各チェックポイントを通ったかのフラグ
	bool m_passCheckPoint[CHECK_POINT_NUMBER];

	//敵のみに使用
	//各AIポイントを通ったかのフラグ
	bool m_passAIPoint[AI_POINT_NUMBER];

	//順位判定に使用する
	//今どのチェックポイントまで通ったか
	int m_nowPoint;

	//AIに使用する
	//次にどのチェックポイントを目指すか
	//チェックポイントの添え字
	int m_nextPoint;

	//今目指しているチェックポイントまでの距離
	float m_nextCheckPointLength;

	//攻撃系アイテムに当たったかのフラグ
	bool m_isHitItem;

	//所持しているアイテム情報
	//持っているアイテムの種類のみを保持しておく
	std::vector<int> m_hasItem;

	void draw();
	void drawHasItem();
	void update();

	void checkCourseOut();
	float checkNextCheckPointLength();
	bool inDart();

	//操作
	void control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY);

	//敵のAI
	void control(); void useItem();

	//周回系
	void printRanking();
	void printStatus();
	void printDashGauge();
	bool countLap();
	bool checkIsGoal();

	void slip();

	//アイテム系
	int hasItemNumber();
	int hasItemLast();

	//コンストラクタ
	Character() :
		CompletionValue(0.f),
		m_type(0),
		m_matrix(glm::mat4(1.f)),
		m_isDash(false),
		m_dashPower(0),
		m_isCharged(false),
		m_dash(nullptr),
		m_dashSpeed(0, 0, 0),
		m_crashRotate(0.f),
		m_wheelSpeed(0.f),
		m_lastPosition(0, 0, 0),
		m_flame(0),
		m_ranking(0),
		m_nowPoint(0),
		m_lapCount(1),
		m_isHitItem(false),
		m_isGoal(false)
	{

		m_engine = new Sound();
		m_engine->loadKukeiha(engine_sound, sizeof(engine_sound), 110);
		m_engine->changeVolume(0.3f);

		//角度からの向きベクトル
		OrientationVector = { -sin(m_rotate.y), -cos(m_rotate.y) };
		m_pos_to_AIpoint = OrientationVector;

		//前輪座標
		m_frontPosition.x = m_position.x - sin(m_rotate.y)*1.55f;
		m_frontPosition.y = 0.f;
		m_frontPosition.z = m_position.z - cos(m_rotate.y)*1.55f;

		//後輪座標
		m_backPosition.x = m_position.x + sin(m_rotate.y)*1.15f;
		m_backPosition.y = 0.f;
		m_backPosition.z = m_position.z + cos(m_rotate.y)*1.15f;


		//ラップタイムの初期化
		for (int i = 0; i < LAP_MAX; i++){
			m_milliSecond[i] = 0;
			m_second[i] = 0;
			m_minute[i] = 0;
		}

		//毎フレーム
		sprintf_s(str_lapCount, "%d", m_lapCount);

		//後で書き換え
		sprintf_s(m_str_lapTime[FIRST], "%02d:%02d:%03d ", m_minute[FIRST], m_second[FIRST], m_milliSecond[FIRST]);
		sprintf_s(m_str_lapTime[SECOND], "%02d:%02d:%03d ", m_minute[SECOND], m_second[SECOND], m_milliSecond[SECOND]);
		sprintf_s(m_str_lapTime[THIRD], "%02d:%02d:%03d ", m_minute[THIRD], m_second[THIRD], m_milliSecond[THIRD]);


		m_scale.x = 0.18f;
		m_scale.y = 0.18f;
		m_scale.z = 0.18f;

	}

	//デストラクタ
	~Character(){ printf("キャラクターが削除されました\n"); }
};

extern GLuint dashIcon;
extern GLuint dashGauge;

extern Character *player1;
extern Character *player2;
extern Character *player3;
extern Character *player4;

extern std::vector<Character*> character;
extern std::vector<Character*> g_useController;
