#include<stdio.h>
#include"joysticManager.h"
#include"controller.h"

JoysticManager* JoysticManager::m_instance = nullptr;

//-------------------------------------------------------------------------------------------------------
//�W���C�X�e�B�b�N�̃C���X�^���X�擾

JoysticManager* JoysticManager::getInstance() {
	if (nullptr == m_instance) {
		m_instance = new JoysticManager();
	}
	return m_instance;
}

//-------------------------------------
//�R���g���[���[���q�����Ă��邩�̃`�F�b�N��
//���݌q�����Ă���R���g���[���[�̑䐔�`�F�b�N

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
//���݌q�����Ă���R���g���[���[�̑䐔��Ԃ�

int JoysticManager::connectingNum(){

	int num = 0;

	for (int i = 0; i < 4; i++){

		if (m_contoroller[i].m_isConnect){
			num++;
		}
	
	}

	return num;
}