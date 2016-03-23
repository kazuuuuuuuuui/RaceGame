#pragma once

/*

Characterクラスのメンバをカプセル化する

*/

#include<vector>
#define _USE_MATH_DEFINES
#include<math.h>
#include"GameObject.h"
#include"Course.h"
#include"Smoke.h"
#include"Dash.h"
#include"xFile.h"
#include"Controller.h"
#include"SoundManager.h"

#define PLAYER_MAX_NUMBER (4)

//1周目 2周目 3周目
#define FIRST (0)
#define SECOND (1)
#define THIRD (2)

#define DASH_GAUGE_MAX (90)

enum
{
	COMPUTER,
	PLAYER
};

	class Character :public oka::GameObject 
	{
	public:

		//自身を操作するコントローラー
		Contoroller m_contoroller;

		//エンジン音
		unsigned int m_engine;

		//自身の向きベクトル
		glm::vec2 OrientationVector;

		//自身の座標からAIポイントまでのベクトル
		glm::vec2 m_pos_to_AIpoint;

		//回転の際の補完値
		float CompletionValue;

		//人が操作するかコンピュータが操作するか
		int m_type;

		//種類
		int m_kind;

		//自身の行列
		glm::mat4 m_matrix;

		//前輪と後輪のポジション
		oka::Vec3 m_frontPosition;
		oka::Vec3 m_backPosition;

		oka::Vec3 m_dashSpeed;

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

		//全体のタイム
		int m_flame;
		int m_milliSecond;
		int m_second;
		int m_minute;
		char m_totalTime[256];

		//ラップタイム
		int m_lapTimeCounter;
		int m_lapMilliSecond[3];
		int m_lapSecond[3];
		int m_lapMinute[3];
		char m_lapTime[3][256];

		//周回数
		//正規の走法でコースを1周したら+1する
		int m_lapCount;
		char m_lap[256];

		//順位
		int m_ranking;

		//レース後の確定順位
		int m_lastRanking;

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

		void Draw();
		void drawHasItem();
		void Update();

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
		Character() {};
		Character(xFile &_body, xFile &_wheel) :
			CompletionValue(0.f),
			m_type(0),
			m_kind(0),
			m_matrix(glm::mat4(1.f)),
			m_isDash(false),
			m_dashPower(0),
			m_isCharged(false),
			m_dash(nullptr),
			m_dashSpeed(0, 0, 0),
			m_crashRotate(0.f),
			m_wheelSpeed(0.f),
			m_flame(0),
			m_lapTimeCounter(0),
			m_ranking(0),
			m_lastRanking(0),
			m_nowPoint(0),
			m_lapCount(0),
			m_isHitItem(false),
			m_isGoal(false)
		{
			printf("プレイヤーが生成されました\n");

			m_body = _body;
			m_backWheel = _wheel;

			m_engine = oka::Sound::LoadSquareWave(engine_sound, sizeof(engine_sound), 110);

			//角度からの向きベクトル
			OrientationVector = { -sin(m_transform.GetRotation().m_y), -cos(m_transform.GetRotation().m_y) };
			m_pos_to_AIpoint = OrientationVector;

			//前輪座標
			m_frontPosition.m_x = m_transform.GetPosition().m_x - sin(m_transform.GetRotation().m_y)*1.55f;
			m_frontPosition.m_y = 0.f;
			m_frontPosition.m_z = m_transform.GetPosition().m_z - cos(m_transform.GetRotation().m_y)*1.55f;

			//後輪座標
			m_backPosition.m_x = m_transform.GetPosition().m_x + sin(m_transform.GetRotation().m_y)*1.15f;
			m_backPosition.m_y = 0.f;
			m_backPosition.m_z = m_transform.GetPosition().m_z + cos(m_transform.GetRotation().m_y)*1.15f;


			//ラップタイムの初期化
			for (int i = 0; i < 3; i++) {
				m_lapMilliSecond[i] = 0;
				m_lapSecond[i] = 0;
				m_lapMinute[i] = 0;
			}

			sprintf_s(m_totalTime, "%02d:%02d:%03d", m_minute, m_second, m_milliSecond);

			sprintf_s(m_lap, "%d", m_lapCount + 1);

			sprintf_s(m_lapTime[FIRST], "%02d:%02d:%03d ", m_lapMinute[FIRST], m_lapSecond[FIRST], m_lapMilliSecond[FIRST]);
			sprintf_s(m_lapTime[SECOND], "%02d:%02d:%03d ", m_lapMinute[SECOND], m_lapSecond[SECOND], m_lapMilliSecond[SECOND]);
			sprintf_s(m_lapTime[THIRD], "%02d:%02d:%03d ", m_lapMinute[THIRD], m_lapSecond[THIRD], m_lapMilliSecond[THIRD]);

			m_transform.SetScale(oka::Vec3(0.18f, 0.18f, 0.18f));

		}

		//デストラクタ
		~Character() { printf("キャラクターが削除されました\n"); }
	};

extern unsigned int dashIcon;
extern unsigned int dashGauge;
