#pragma once 

#include"Course.h"
#include"GameObject.h"
#include"glut.h"

//�A�C�e���`��
//�X�t�B�A�}�b�s���O�p��
#define ITEM_RADIUS (0.4f)
#define ITEM_SLICE (10)
#define ITEM_STACK (10)
#define ITEM_REPEAT_S (1)
#define ITEM_REPEAT_T (1)

//�v���C���[�������ł���ő�A�C�e����
#define HAS_ITEM_MAX (3)


//-------------------------------------
//���΂̎��
/*
�E�t�@�C�A
�E�u���U�h
*/

enum {
	FIRE = 0,
	BLIZZARD,
	//HASTE,

	ITEM_TYPE_MAX
};


void Circle2DFill(float radius, int x, int y);


//-------------------------------------
//����(�A�C�e��)�̏��


class Item : public oka::GameObject{
public:

	//��芸����
	int m_flame;

	int m_type;

	//�g�p���ꂽ�Ƃ���false�ɂȂ�
	//�f�t�H���g��true
	bool m_isActive;

	//���b��1��A�C�e�����ďo��������
	void reCreateItem();

	//�v���C���[�ɂƂ�ꂽ���ǂ����𔻒肷��
	bool checkIsGotten(oka::Vec3 _position);

	//�R���X�g���N�^
	Item() :
		m_flame(0),
		m_type(rand() % ITEM_TYPE_MAX),
		m_isActive(true)

	{};

	void move();
	void Draw();
	void Update();

};

extern int itemNum;
