#include"ItemManager.h"

//-------------------------------------
//�R���X�g���N�^

//�L�����N�^�[�̃��f���f�[�^�̓ǂݍ��݂��s�� //��ŏ�������

//�}�l�[�W���[�������Ƀv���C���[�̐���
//�L�����N�^�[���Ǘ�����x�N�^�[�ɑ΂���new����push����

ItemManager::ItemManager()
{
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