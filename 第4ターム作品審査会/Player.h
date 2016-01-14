#pragma once


//debug
//�f�o�b�O�p�Ɉʒu�������悤�ɂ��Ă���
#define PLAYER_TEST_POS_X (20.f)
#define PLAYER_TEST_POS_Y (0.5f)
#define PLAYER_TEST_POS_Z (-160.f)

//�v���C���[�������o���閂�΂̍ő吔
#define MAGICSTONE_MAX (3)

//�v���C���[���������Ă��閂�΂�1��
#define MAGICSTONE_FIRST (0)

//�v���C���[���������Ă��閂�΂�2��
#define MAGICSTONE_SECOND (1)

//�v���C���[���������Ă��閂�΂�3��
#define MAGICSTONE_THIRD (2)

#include<vector>
#include"FlyingObject.h"
#include"MagicStone.h"
#include"xFile.h"

//-------------------------------------
//���@�̏��

class Player :public FlyingObject{
public:

	//�ԑ̕���
	xFile m_boby;

	//���_��
	unsigned int m_vertices;

	//�C���f�b�N�X��
	unsigned int m_indeces;

	//���_���
	std::vector<float>m_vertex;

	//�C���f�b�N�X���
	std::vector<unsigned short>m_index;

	//�@�����
	std::vector<float>m_normal;


	//����
	//���K�̑��@�ŃR�[�X��1��������+1����
	int m_lapCount;

	//�`�F�b�N�|�C���g�����������true�ɂȂ�
	//m_lapCount��+1���ꂽ�ۂɂ��ׂẴt���O��false�ɖ߂�
	bool m_checkFlag;

	MagicStone m_magicStone[MAGICSTONE_MAX];

	void draw();
	void update();
	void control(unsigned int _key, float _x, float _y, float _z);

	void checkCourseOut();

	bool inDart();

	bool getMagicStone();

	bool passCheckPoint();
	bool countLap();
	bool isGoal();

	//��ŏ���������
	Player() :
		m_lapCount(0),
		m_checkFlag(false)
	{
		m_position.x = PLAYER_TEST_POS_X;
		m_position.y = PLAYER_TEST_POS_Y;
		m_position.z = PLAYER_TEST_POS_Z;

		/*m_scale.x = 0.15f;
		m_scale.y = 0.15f;
		m_scale.z = 0.15f;*/
	}

};

extern Player *player;