#include"ItemManager.h"

//-------------------------------------
//�R���X�g���N�^

ItemManager::ItemManager()
{
	//debug
	printf("�A�C�e���}�l�[�W���[����\n");
	printf("\n");

	m_itemNum = 0;

	for (unsigned int i = 0; i < SET_ITEM_NUMBER; i++)
	{
		m_item.push_back(new Item());
	}

}

ItemManager* ItemManager::m_instance = nullptr;

//-------------------------------------
//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�

ItemManager* ItemManager::GetInstance()
{
	if (nullptr == m_instance)
	{
		m_instance = new ItemManager();
	}

	return m_instance;
}

//-------------------------------------
//���g��nullptr�łȂ��ꍇ�������g��j������

void ItemManager::Destory()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}