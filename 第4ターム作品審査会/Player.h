#pragma once

//debug
//�f�o�b�O�p�Ɉʒu�������悤�ɂ��Ă���
#define PLAYER_TEST_POS_X (20.f)
#define PLAYER_TEST_POS_Y (0.5f)
#define PLAYER_TEST_POS_Z (-160.f)

//�v���C���[�������o���閂�΂̍ő吔
#define MAGICSTONE_MAX (3)

#define FIRST (0)
#define SECOND (1)
#define THIRD (2)

#include<vector>
#include"GameObject.h"
#include"Item.h"
#include"xFile.h"
#include"FireEffect.h"

//-------------------------------------
//���@�̏��

class Player :public GameObject{
public:

	//�ԑ̕���
	xFile m_boby;

	//��֕���
	xFile m_backWheel;

	//����
	//���K�̑��@�ŃR�[�X��1��������+1����
	int m_lapCount;

	//����
	int m_ranking;

	//����̎��񐔂ɒB������true�ɂȂ�
	bool m_isGoal;

	bool m_passCheckPoint[CHECK_POINT_NUMBER];
	//bool m_checkFlag;

	//���b�v�^�C��
	int m_flame;
	int m_milliSecond[LAP_MAX];
	int m_second[LAP_MAX];
	int m_minute[LAP_MAX];
	char m_str_lapTime[LAP_MAX][256];

	//�������Ă��閂�Ώ��
	//���΂������|�C���^�̃x�N�^�[
	std::vector<Item*> m_hasMagicStone;

	//�t�@�C�A���g�����Ƃ��̃G�t�F�N�g���Ǘ�
	std::vector<FireEffect*> m_useFire;

	void draw();
	void update();
	void control(unsigned int _pressedKey, unsigned int _downKeys, float _x, float _y, float _z);

	void checkCourseOut();

	bool inDart();

	//����n
	bool countLap();
	bool checkIsGoal();

	//�A�C�e���n
	int hasMagicStoneNumber();



	//��ŏ���������
	Player() :
		m_flame(0),
		m_lapCount(1),
		m_ranking(1),
		m_isGoal(false)

	{
		//debug
		m_position.x = PLAYER_TEST_POS_X;
		m_position.y = PLAYER_TEST_POS_Y;
		m_position.z = PLAYER_TEST_POS_Z;

		m_scale.x = 0.18f;
		m_scale.y = 0.18f;
		m_scale.z = 0.18f;

		//���b�v�^�C���̏�����
		for (int i = 0; i < LAP_MAX; i++){
			m_milliSecond[i] = 0;
			m_second[i] = 0;
			m_minute[i] = 0;
		}

	}

};

extern Player *player;