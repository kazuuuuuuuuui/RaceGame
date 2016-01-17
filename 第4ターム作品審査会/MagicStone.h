#pragma once 

#include"Course.h"
#include"FlyingObject.h"
#include"glut.h"

//�R�[�X�ɔz�u����Ă��閂�΂̐�
#define SET_MAGICSTONE_NUMBER (20)

//-------------------------------------
//���΂̎��
/*
�E�t�@�C�A
�E�u���U�h
�E�T���_�[

�E�w�C�X�g
�E�~�j�}��
�E�A���e�}


*/

enum {
	FIRE = 0,
	BLIZZARD,
	//HASTE,

	MAGIC_TYPE_MAX
};



//-------------------------------------
//����(�A�C�e��)�̏��


class MagicStone : public FlyingObject{
public:

	int m_type;

	//�v���C���[�ɂ���Ď擾����Ă��邩�̃t���O
	//�f�t�H���g��false
	bool m_isGotten;

	//�g�p���ꂽ�Ƃ���false�ɂȂ�
	//�f�t�H���g��true
	bool m_isActive;

	//�v���C���[�ɂƂ�ꂽ���ǂ����𔻒肷��
	bool checkIsGotten();

	//�R���X�g���N�^
	MagicStone() :
		m_type(rand() % MAGIC_TYPE_MAX),
		m_isGotten(false),
		m_isActive(true)

	{};

	void draw();
	void update();

};

extern MagicStone *magicStone[SET_MAGICSTONE_NUMBER];
extern GLuint fire_handle;
extern GLuint blizzard_handle;
extern GLuint haste_handle;