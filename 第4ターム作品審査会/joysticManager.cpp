#include<stdio.h>
#include"JoysticManager.h"

namespace oka
{
	JoysticManager* JoysticManager::m_instance = nullptr;

	//-------------------------------------------------------------------------------------------------------
	//�W���C�X�e�B�b�N�̃C���X�^���X�擾

	JoysticManager* JoysticManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new JoysticManager();
		}

		return m_instance;
	}


	//-------------------------------------
	//�L�����N�^�[�ƃR���g���[���̑Ή��t��
	//�����Ƃ��ăL�����N�^�^�̃|�C���^���󂯎��
	//�R���g���[�����Ǘ����Ă���x�N�^�[�ɓ����

	void JoysticManager::AddController(Contoroller *_controller)
	{
		m_contoroller.push_back(_controller);
	}

	//-------------------------------------
	//

	unsigned int JoysticManager::GetContorollerNumber()const
	{
		return m_contoroller.size();
	}



	Contoroller JoysticManager::GetContoroller(const int _num)const
	{
		return *(m_contoroller[_num]);	
	}

	//-------------------------------------
	//�R���g���[���[���q�����Ă��邩�̃`�F�b�N��
	//���݌q�����Ă���R���g���[���[�̑䐔�`�F�b�N

	void JoysticManager::Update()
	{
		for (unsigned int i = 0; i < m_contoroller.size(); i++)
		{
			if (ERROR_SUCCESS == XInputGetState(i, &m_contoroller[i]->m_state))
			{
				m_contoroller[i]->m_isConnect = true;
				m_contoroller[i]->Update();
			}
			else
			{
				m_contoroller[i]->m_isConnect = false;
			}

		}

	}



}