#pragma once 

#include"Course.h"
#include"FlyingObject.h"
#include"glut.h"

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
	Blizzard,
	Thunder,

	MAGIC_TYPE_MAX
};



//-------------------------------------
//����(�A�C�e��)�̏��


class MagicStone : public FlyingObject{
public:

	int m_type;
	bool m_isActive;

	//�R���X�g���N�^
	MagicStone() :
		m_type(FIRE),
		m_isActive(false)

		//��ŏ�������
	{
		m_position.x = 20.f;
		m_position.y = 0.5;
		m_position.z = -190.f;
	};

	void draw();

};

extern MagicStone *magicStone;
extern GLuint fire_handle;
extern GLuint blizzard_handle;