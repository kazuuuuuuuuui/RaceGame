#pragma once

#include<Windows.h>
#include<Xinput.h>

#pragma comment (lib,"xinput.lib")

class Contoroller
{
public:

	XINPUT_STATE m_state;

	bool m_isConnect;
	
	//���t���[���̃X�e�B�b�Nx�����̏��
	float m_sThumbLX;

	bool m_xRightDown;
	bool m_xRightLast;

	bool m_xLeftDown;
	bool m_xLeftLast;

	//���t���[���̃X�e�B�b�Ny�����̏��
	float m_sThumbLY;

	bool m_yTopDown;
	bool m_yTopLast;

	bool m_yBottomDown;
	bool m_yBottomLast;

	unsigned int m_pressedKey;//���t���[��������Ă���L�[
	unsigned int m_lastkey;//�O�t���[���O�ɉ�����Ă����L�[
	unsigned int m_changedKey;//�O�t���[���ƌ��t���[���ŕω����������L�[
	unsigned int m_downkey;

	void Update();
	void stick_x();
	void stick_y();

	Contoroller():
		m_isConnect(false),
		m_sThumbLX(0.0f), m_sThumbLY(0.0f),
		m_xRightDown(false), m_xRightLast(false), m_xLeftDown(false), m_xLeftLast(false),
		m_yTopDown(false), m_yTopLast(false), m_yBottomDown(false), m_yBottomLast(false),
		m_pressedKey(0),m_lastkey(0),m_changedKey(0),m_downkey(0)
	{};

};
