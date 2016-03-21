#include<stdio.h>
#include"controller.h"

void Contoroller::Update()
{

	//ボタン
	m_pressedKey = m_state.Gamepad.wButtons;
	m_changedKey = m_pressedKey ^ m_lastkey;
	m_downkey = m_pressedKey & m_changedKey;

	//スティック
	m_sThumbLX = m_state.Gamepad.sThumbLX;
	m_sThumbLY = m_state.Gamepad.sThumbLY;

	//-32768～32767の値を-1～1の値に変換
	m_sThumbLX /= 32768;
	m_sThumbLY /= 32768;

	stick_x();
	stick_y();

	m_lastkey = m_state.Gamepad.wButtons;

}

//-------------------------------------
//スティックの傾きによるxトリガーのON・OFF

void Contoroller::stick_x()
{
	bool m_xLeftPressed;
	bool m_xRightPressed;

	bool m_xLeftChanged;
	bool m_xRightChanged;

	if (m_sThumbLX > 0.5)
	{
		m_xRightPressed = true;
		m_xLeftPressed = false;
	}
	else if (m_sThumbLX < -0.5)
	{
		m_xRightPressed = false;
		m_xLeftPressed = true;
	}
	else
	{
		m_xRightPressed = false;
		m_xLeftPressed = false;
	}

	m_xRightChanged = m_xRightPressed^m_xRightLast;
	m_xLeftChanged = m_xLeftPressed^m_xLeftLast;

	m_xRightDown = m_xRightPressed & m_xRightChanged;
	m_xLeftDown = m_xLeftPressed & m_xLeftChanged;
	
	m_xLeftLast = m_xLeftPressed;
	m_xRightLast = m_xRightPressed;
}

//-------------------------------------
//スティックの傾きによるyトリガーのON・OFF

void Contoroller::stick_y()
{
	bool m_yTopPressed;
	bool m_yBottomPressed;

	bool m_yTopChanged;
	bool m_yBottomChanged;

	if (m_sThumbLY > 0.5){
		m_yTopPressed = true;
		m_yBottomPressed = false;
	}
	else if (m_sThumbLY < -0.5){
		m_yTopPressed = false;
		m_yBottomPressed = true;
	}
	else{
		m_yTopPressed = false;
		m_yBottomPressed = false;
	}

	m_yTopChanged = m_yTopPressed^m_yTopLast;
	m_yBottomChanged = m_yBottomPressed^m_yBottomLast;

	m_yTopDown = m_yTopPressed & m_yTopChanged;
	m_yBottomDown = m_yBottomPressed & m_yBottomChanged;

	m_yTopLast = m_yTopPressed;
	m_yBottomLast = m_yBottomPressed;
}