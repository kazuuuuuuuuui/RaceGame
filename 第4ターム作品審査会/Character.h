#pragma once

/*

Character�N���X�̃����o���J�v�Z��������

*/

#include<vector>
#define _USE_MATH_DEFINES
#include<math.h>
#include"GameObject.h"
#include"Course.h"
#include"Smoke.h"
#include"xFile.h"
#include"Controller.h"
#include"SoundManager.h"
#include"BikeBody.h"
#include"BikeWheel.h"

#define PLAYER_MAX_NUMBER (4)

//1���� 2���� 3����
#define FIRST (0)
#define SECOND (1)
#define THIRD (2)

#define DASH_GAUGE_MAX (90)

	class Character :public oka::GameObject 
	{
	public:

		//���g�𑀍삷��R���g���[���[
		//Contoroller m_contoroller;

		//�G���W����
		//unsigned int m_engine;

		//���g�̌����x�N�g��
		glm::vec2 OrientationVector;

		//���g�̍��W����AI�|�C���g�܂ł̃x�N�g��
		glm::vec2 m_pos_to_AIpoint;

		//��]�̍ۂ̕⊮�l
		float CompletionValue;

		//�O�ւƌ�ւ̃|�W�V����
		//oka::Vec3 m_frontPosition;
		//oka::Vec3 m_backPosition;

		oka::Vec3 m_dashSpeed;

		//�A�C�e���ɓ����������̉�]�l
		float m_crashRotate;

		//�ԗւ̉�]�X�s�[�h
		float m_wheelSpeed;

		//�ԑ̕���
		BikeBody m_body;

		//��֕���
		BikeWheel m_frontWheel;
		BikeWheel m_backWheel;

		//�ԑ̂���o�鉌
		Smoke m_smoke;

		//�_�b�V����Ԃ��ǂ����̃t���O
		bool m_isDash;

		//�_�b�V���ɕK�v�ȗ�
		//��15�b��1��g����悤�ɗ��܂��Ă���
		float m_dashPower;

		//�_�b�V���p���[�����܂����ۂ�true�ɂȂ�
		bool m_isCharged;

		//�S�̂̃^�C��
		int m_flame;
		int m_milliSecond;
		int m_second;
		int m_minute;
		char m_totalTime[256];

		//���b�v�^�C��
		int m_lapTimeCounter;
		int m_lapMilliSecond[3];
		int m_lapSecond[3];
		int m_lapMinute[3];
		char m_lapTime[3][256];

		//����
		//���K�̑��@�ŃR�[�X��1��������+1����
		int m_lapCount;
		char m_lap[256];

		//����
		int m_ranking;

		//���[�X��̊m�菇��
		int m_lastRanking;

		//����̎��񐔂ɒB������true�ɂȂ�
		bool m_isGoal;


		//�e�`�F�b�N�|�C���g��ʂ������̃t���O
		bool m_passCheckPoint[Course::checkPointNum];

		//�G�݂̂Ɏg�p
		//�eAI�|�C���g��ʂ������̃t���O
		bool m_passAIPoint[Course::aimPointNum];

		//���ʔ���Ɏg�p����
		//���ǂ̃`�F�b�N�|�C���g�܂Œʂ�����
		int m_nowPoint;

		//AI�Ɏg�p����
		//���ɂǂ̃`�F�b�N�|�C���g��ڎw����
		//�`�F�b�N�|�C���g�̓Y����
		int m_nextPoint;

		//���ڎw���Ă���`�F�b�N�|�C���g�܂ł̋���
		float m_nextCheckPointLength;

		//�U���n�A�C�e���ɓ����������̃t���O
		bool m_isHitItem;

		//�������Ă���A�C�e�����
		//�����Ă���A�C�e���̎�ނ݂̂�ێ����Ă���
		std::vector<int> m_hasItem;

		void Draw();
		void drawHasItem();
		void Update();

		void checkCourseOut();
		float checkNextCheckPointLength();
		bool inDart();

		//����
		void control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY);

		//�G��AI
		void control(); void useItem();

		//����n
		void printRanking();
		void printStatus();
		void printDashGauge();
		bool countLap();
		bool checkIsGoal();

		void slip();

		//�A�C�e���n
		int hasItemNumber();
		int hasItemLast();

		//�R���X�g���N�^
		Character() {};
		Character(xFile &_body, xFile &_wheel) :
			CompletionValue(0.f),
			m_isDash(false),
			m_dashPower(0),
			m_isCharged(false),
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
			//debug
			printf("�v���C���[����������܂���\n");

			m_body.m_model = _body;
			m_frontWheel.m_model = _wheel;
			m_backWheel.m_model = _wheel;

			m_transform.SetScale(oka::Vec3(0.18f, 0.18f, 0.18f));

			//m_engine = oka::Sound::LoadSquareWave(engine_sound, sizeof(engine_sound), 110);

			//�p�x����̌����x�N�g��
			OrientationVector = { -sin(m_transform.GetRotation().m_y), -cos(m_transform.GetRotation().m_y) };
			m_pos_to_AIpoint = OrientationVector;

			//�O�֍��W
			//m_frontPosition.m_x = m_transform.GetPosition().m_x - sin(m_transform.GetRotation().m_y)*1.55f;
			//m_frontPosition.m_y = 0.f;
			//m_frontPosition.m_z = m_transform.GetPosition().m_z - cos(m_transform.GetRotation().m_y)*1.55f;

			////��֍��W
			//m_backPosition.m_x = m_transform.GetPosition().m_x + sin(m_transform.GetRotation().m_y)*1.15f;
			//m_backPosition.m_y = 0.f;
			//m_backPosition.m_z = m_transform.GetPosition().m_z + cos(m_transform.GetRotation().m_y)*1.15f;


			//���b�v�^�C���̏�����
			for (int i = 0; i < 3; i++) 
			{
				m_lapMilliSecond[i] = 0;
				m_lapSecond[i] = 0;
				m_lapMinute[i] = 0;
			}

			sprintf_s(m_totalTime, "%02d:%02d:%03d", m_minute, m_second, m_milliSecond);

			sprintf_s(m_lap, "%d", m_lapCount + 1);

			sprintf_s(m_lapTime[FIRST], "%02d:%02d:%03d ", m_lapMinute[FIRST], m_lapSecond[FIRST], m_lapMilliSecond[FIRST]);
			sprintf_s(m_lapTime[SECOND], "%02d:%02d:%03d ", m_lapMinute[SECOND], m_lapSecond[SECOND], m_lapMilliSecond[SECOND]);
			sprintf_s(m_lapTime[THIRD], "%02d:%02d:%03d ", m_lapMinute[THIRD], m_lapSecond[THIRD], m_lapMilliSecond[THIRD]);

		}

		//�f�X�g���N�^
		~Character() 
		{
			//debug
			printf("�L�����N�^�[���폜����܂���\n"); 
		}
	};


