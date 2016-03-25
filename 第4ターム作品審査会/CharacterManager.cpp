#include"CharacterManager.h"
#include"xFile.h"

	//-------------------------------------
	//�R���X�g���N�^

	//�L�����N�^�[�̃��f���f�[�^�̓ǂݍ��݂��s�� //��ŏ�������
	
	//�}�l�[�W���[�������Ƀv���C���[�̐���
	//�L�����N�^�[���Ǘ�����x�N�^�[�ɑ΂���new����push����

	CharacterManager::CharacterManager()
	{
		xFile body;
		xFile wheel;

		//���f���f�[�^�̓ǂݍ���
		xFile::loadXfile("xFile/bike.x", body);
		xFile::loadXfile("xFile/taiya.x", wheel);

		//�ԑ̂̃��f���f�[�^�̌����C��
		body.rotate();

		for (int i = 0; i < PLAYER_MAX_NUMBER; i++)
		{
			m_character.push_back(new Character(body, wheel));
		}
	}
	
	
	CharacterManager* CharacterManager::m_instance = nullptr;

	//-------------------------------------
	//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
	//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�

	CharacterManager* CharacterManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new CharacterManager();
		}

		return m_instance;
	}

	//-------------------------------------
	//�v���C���[�̐���Ԃ�

	unsigned int CharacterManager::GetCharacterNumber()const
	{
		return m_character.size();
	}

