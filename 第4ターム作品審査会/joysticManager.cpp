#include<stdio.h>
#include"joysticManager.h"
#include"controller.h"

JoysticManager* JoysticManager::m_instance = nullptr;

//-------------------------------------------------------------------------------------------------------
//ジョイスティックのインスタンス取得

JoysticManager* JoysticManager::getInstance() {
	if (nullptr == m_instance) {
		m_instance = new JoysticManager();
	}
	return m_instance;
}

//-------------------------------------
//コントローラーが繋がっているかのチェックと
//現在繋がっているコントローラーの台数チェック

void JoysticManager::update(){

	for (int i = 0; i < 4; i++){

		if (ERROR_SUCCESS == XInputGetState(i, &m_contoroller[i].m_state)){
			m_contoroller[i].m_isConnect = true;
			m_contoroller[i].update();
		}
		else{
			m_contoroller[i].m_isConnect = false;
		}

	}

}

//-------------------------------------
//現在繋がっているコントローラーの台数を返す

int JoysticManager::connectingNum(){

	int num = 0;

	for (int i = 0; i < 4; i++){

		if (m_contoroller[i].m_isConnect){
			num++;
		}
	
	}

	return num;
}