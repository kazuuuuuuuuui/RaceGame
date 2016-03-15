#pragma once

#include<Windows.h>
#include<Xinput.h>

#pragma comment (lib,"xinput.lib")

class contoroller
{
public:

	XINPUT_STATE m_state;
	
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

	bool m_isConnect;

	void update();
	void stick_x();
	void stick_y();

	contoroller(){};

};
