#pragma once

#include<vector>
#define _USE_MATH_DEFINES
#include<math.h>
#include"GameObject.h"
#include"Course.h"
#include"Smoke.h"
#include"Dash.h"
#include"xFile.h"

//1周目 2周目 3周目
#define FIRST (0)
#define SECOND (1)
#define THIRD (2)

#define DASH_GAUGE_MAX (90)

enum{
	PLAYER0,
	PLAYER1,
	PLAYER2,
	PLAYER3,
};

class Character :public GameObject{
public:


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

	//ファイアを使ったときのエフェクトを管理
	//std::vector<FireEffect*> m_useFire;

	void draw();
	void drawHasItem();
	void update();

	void checkCourseOut();
	float checkNextCheckPointLength();
	bool inDart();

	//周回系
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
		m_dash(nullptr),
		m_dashSpeed(0,0,0),
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

		//前輪座標
		m_frontPosition.x = m_position.x - sin(m_rotate.y)*1.55f;
		m_frontPosition.y = 0.f;
		m_frontPosition.z = m_position.z - cos(m_rotate.y)*1.55f;

		//後輪座標
		m_backPosition.x = m_position.x + sin(m_rotate.y)*1.15f;
		m_backPosition.y = 0.f;
		m_backPosition.z = m_position.z + cos(m_rotate.y)*1.15f;

		//煙の座標
		/*m_smoke.m_basePosition.x = m_position.x + sin(m_rotate.y)*1.3f;
		m_smoke.m_basePosition.y = 1.f;
		m_smoke.m_basePosition.z = m_position.x + cos(m_rotate.y)*1.3f;*/

		//ラップタイムの初期化
		for (int i = 0; i < LAP_MAX; i++){
			m_milliSecond[i] = 0;
			m_second[i] = 0;
			m_minute[i] = 0;
		}
		m_scale.x = 0.18f;
		m_scale.y = 0.18f;
		m_scale.z = 0.18f;

	}
};

extern std::vector<Character*> character;