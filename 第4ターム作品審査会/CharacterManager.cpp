#include"CharacterManager.h"

#include"GameManager.h"
#include"xFile.h"

CharacterManager* CharacterManager::m_instance = nullptr;

	//-------------------------------------
	//�R���X�g���N�^

	//�L�����N�^�[�̃��f���f�[�^�̓ǂݍ��݂��s�� //��ŏ�������
	
	//�}�l�[�W���[�������Ƀv���C���[�̐���
	//�L�����N�^�[���Ǘ�����x�N�^�[�ɑ΂���new����push����

	CharacterManager::CharacterManager()
	{	
		printf("�L�����N�^�[�}�l�[�W���[����\n");
		printf("\n");

		xFile body;
		xFile wheel;

		//���f���f�[�^�̓ǂݍ���
		xFile::loadXfile("xFile/bike.x", body);
		xFile::loadXfile("xFile/taiya.x", wheel);

		//�ԑ̂̃��f���f�[�^�̌����C��
		body.rotate();

		for (int i = 0; i < PLAYER_MAX_NUMBER; i++)
		{
			Character *character = new Character(body, wheel);
			m_character.push_back(character);
			oka::GameManager::GetInstance()->AddGameObject(character);
		}
	}


	//-------------------------------------
	//�f�X�g���N�^
	//

	CharacterManager::~CharacterManager()
	{
		//debug
		printf("�L�����N�^�[�}�l�[�W���[�폜\n");
		printf("\n");
	
	/*	for (unsigned int i = 0; m_character.size(); i++)
		{
			delete m_character[i];
		}*/
		
		m_character.clear();
	
	};
	

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
	//���g��nullptr�łȂ��ꍇ�������g��j������

	void CharacterManager::Destroy()
	{
		if(m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	//-------------------------------------
	//�v���C���[�̐���Ԃ�

	unsigned int CharacterManager::GetCharacterNumber()const
	{
		return m_character.size();
	}

