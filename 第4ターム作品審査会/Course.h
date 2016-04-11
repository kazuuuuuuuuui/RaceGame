#ifndef COURSE_H_
#define COURSE_H_

//�K���g�p����e�N�X�`���̏c���ƃT�C�Y�����킹�邱��
#define COURSE_WIDTH (256)
#define COURSE_HEIGHT (256)

//�R�[�X�ɔz�u����Ă��閂�΂̐�
#define SET_ITEM_NUMBER (20)

#include<stdlib.h>
#include<vector>
#include"Item.h"
#include"BmpImage.h"
#include"CheckPoint.h"
#include"GameObject.h"
#include"AimPoint.h"
#include"Sound.h"
#include"Vec3.h"
#include"glut.h"

//-------------------------------------
//�R�[�X�̊e�s�N�Z���̏��

enum 
{
	PATH = 0,
	DART,
	START,
	GOAL,
	ITEMPOSITION
};


//-------------------------------------
//�R�[�X�̏��

class Course :public oka::GameObject 
{
public:

	const char *m_name;

	//�R�[�X�ɐݒu���Ă���
	//���񔻒�p�̃`�F�b�N�|�C���g�̌�
	static const int checkPointNum = 10;

	//�R�[�X�ɐݒu���Ă���
	//�G�L����AI�p�̃|�C���g�̌�
	static const int aimPointNum = 25;

	//���_��
	unsigned int m_vertices;

	//�C���f�b�N�X��
	unsigned int m_indeces;

	//���_���
	std::vector<oka::Vec3>m_vertex;

	//�C���f�b�N�X���
	std::vector<unsigned short>m_index;

	//�@�����
	std::vector<oka::Vec3>m_normal;

	//uv���
	std::vector<glm::vec2>m_tex;

	int m_width;
	int m_height;

	int m_depth;

	int m_buffer[COURSE_HEIGHT][COURSE_WIDTH];   //�e�R�[�X�̊e�s�N�Z���̏����i�[����o�b�t�@
	
	unsigned int m_handle;							 //�R�[�X�̃e�N�X�`��
	unsigned int m_bgm;
	
	CheckPoint m_checkPoint[checkPointNum]; //���񔻒�p�̃|�C���g
	AimPoint m_aimPoint[aimPointNum];			 //�GAI�p�̃|�C���g
	
	static const oka::Vec3 m_backgroundColor;

	void Draw();
	void Update() {};

	void SetVertex();
	void SetIndex();
	void SetNormal();
	void SetTex();
	void SetHeight(const char *_fileName);
	
	void MakeBuffer(const char *_fileName);

	void SetItem();
	void SetCheckPoint(const char *_txtName);
	void SetAimPoint(const char *_txtName);

	Course();
	~Course();

};

#endif

