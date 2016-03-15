#pragma once

#include<Windows.h>
#include<Xinput.h>

#pragma comment (lib,"xinput.lib")

class contoroller
{
public:

	XINPUT_STATE m_state;
	
	//現フレームのスティックx方向の情報
	float m_sThumbLX;

	bool m_xRightDown;
	bool m_xRightLast;

	bool m_xLeftDown;
	bool m_xLeftLast;

	//現フレームのスティックy方向の情報
	float m_sThumbLY;

	bool m_yTopDown;
	bool m_yTopLast;

	bool m_yBottomDown;
	bool m_yBottomLast;

	unsigned int m_pressedKey;//現フレーム押されているキー
	unsigned int m_lastkey;//前フレーム前に押されていたキー
	unsigned int m_changedKey;//前フレームと現フレームで変化があったキー
	unsigned int m_downkey;

	bool m_isConnect;

	void update();
	void stick_x();
	void stick_y();

	contoroller(){};

};
