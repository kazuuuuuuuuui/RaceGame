#pragma once

#include<vector>
#define _USE_MATH_DEFINES
#include<math.h>
#include"GameObject.h"
#include"Course.h"
#include"Smoke.h"
#include"Dash.h"
#include"xFile.h"

//1���� 2���� 3����
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


	//���g�̌����x�N�g��
	glm::vec2 OrientationVector;

	//���g�̍��W����AI�|�C���g�܂ł̃x�N�g��
	glm::vec2 m_pos_to_AIpoint;

	//��]�̍ۂ̕⊮�l
	float CompletionValue;

	//���
	int m_type;

	//���g�̍s��
	glm::mat4 m_matrix;

	//1�t���[���O�̃|�W�V����
	glm::vec3 m_lastPosition;

	//�O�ւƌ�ւ̃|�W�V����
	glm::vec3 m_frontPosition;
	glm::vec3 m_backPosition;

	glm::vec3 m_dashSpeed;

	//�A�C�e���ɓ����������̉�]�l
	float m_crashRotate;

	//�ԗւ̉�]�X�s�[�h
	float m_wheelSpeed;

	//�ԑ̕���
	xFile m_body;

	//��֕���
	xFile m_backWheel;

	//�ԑ̂���o�鉌
	Smoke m_smoke;

	//�_�b�V����Ԃ��ǂ����̃t���O
	bool m_isDash;

	//�_�b�V���ɕK�v�ȗ�
	//��15�b��1��g����悤�ɗ��܂��Ă���
	float m_dashPower;

	//�_�b�V�����̃G�t�F�N�g
	Dash *m_dash;

	//���b�v�^�C��
	int m_flame;
	int m_milliSecond[LAP_MAX];
	int m_second[LAP_MAX];
	int m_minute[LAP_MAX];
	char m_str_lapTime[LAP_MAX][256];

	//����
	//���K�̑��@�ŃR�[�X��1��������+1����
	int m_lapCount;

	//����
	int m_ranking;

	//����̎��񐔂ɒB������true�ɂȂ�
	bool m_isGoal;


	//�e�`�F�b�N�|�C���g��ʂ������̃t���O
	bool m_passCheckPoint[CHECK_POINT_NUMBER];

	//�G�݂̂Ɏg�p
	//�eAI�|�C���g��ʂ������̃t���O
	bool m_passAIPoint[AI_POINT_NUMBER];

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

	//�t�@�C�A���g�����Ƃ��̃G�t�F�N�g���Ǘ�
	//std::vector<FireEffect*> m_useFire;

	void draw();
	void drawHasItem();
	void update();

	void checkCourseOut();
	float checkNextCheckPointLength();
	bool inDart();

	//����n
	bool countLap();
	bool checkIsGoal();

	void slip();

	//�A�C�e���n
	int hasItemNumber();
	int hasItemLast();

	//�R���X�g���N�^
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

		//�O�֍��W
		m_frontPosition.x = m_position.x - sin(m_rotate.y)*1.55f;
		m_frontPosition.y = 0.f;
		m_frontPosition.z = m_position.z - cos(m_rotate.y)*1.55f;

		//��֍��W
		m_backPosition.x = m_position.x + sin(m_rotate.y)*1.15f;
		m_backPosition.y = 0.f;
		m_backPosition.z = m_position.z + cos(m_rotate.y)*1.15f;

		//���̍��W
		/*m_smoke.m_basePosition.x = m_position.x + sin(m_rotate.y)*1.3f;
		m_smoke.m_basePosition.y = 1.f;
		m_smoke.m_basePosition.z = m_position.x + cos(m_rotate.y)*1.3f;*/

		//���b�v�^�C���̏�����
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