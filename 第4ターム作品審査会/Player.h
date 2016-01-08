#pragma once

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

	MagicStone m_magicStone[MAGICSTONE_MAX];

	void draw();
	void update();
	void control(unsigned int _key, float _x, float _y, float _z);
	bool inDart();
	bool getMagicStone();

	//��ŏ���������
	Player(){
		m_position.x = 22.f;
		m_position.y = 0.5f;
		m_position.z = -68.f;

		/*m_scale.x = 0.1f;
		m_scale.y = 0.1f;
		m_scale.z = 0.1f;*/
	}

};

extern Player *player;