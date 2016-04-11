#include"CharacterManager.h"

#include"GameManager.h"
#include"xFile.h"

CharacterManager* CharacterManager::m_instance = nullptr;

	//-------------------------------------
	//コンストラクタ

	//キャラクターのモデルデータの読み込みを行い //後で書き換え
	
	//マネージャー生成時にプレイヤーの数分
	//キャラクターを管理するベクターに対してnewしてpushする

	CharacterManager::CharacterManager()
	{	
		printf("キャラクターマネージャー生成\n");
		printf("\n");

		xFile body;
		xFile wheel;

		//モデルデータの読み込み
		xFile::loadXfile("xFile/bike.x", body);
		xFile::loadXfile("xFile/taiya.x", wheel);

		//車体のモデルデータの向き修正
		body.rotate();

		for (int i = 0; i < PLAYER_MAX_NUMBER; i++)
		{
			Character *character = new Character(body, wheel);
			m_character.push_back(character);
			oka::GameManager::GetInstance()->AddGameObject(character);
		}
	}


	//-------------------------------------
	//デストラクタ
	//

	CharacterManager::~CharacterManager()
	{
		//debug
		printf("キャラクターマネージャー削除\n");
		printf("\n");
	
	/*	for (unsigned int i = 0; m_character.size(); i++)
		{
			delete m_character[i];
		}*/
		
		m_character.clear();
	
	};
	

	//-------------------------------------
	//シングルトンにするためインスタンスがない場合のみnewし
	//既にインスタンスがある場合はそのインスタンスをそのまま返す

	CharacterManager* CharacterManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new CharacterManager();
		}

		return m_instance;
	}


	//-------------------------------------
	//自身がnullptrでない場合自分自身を破棄する

	void CharacterManager::Destroy()
	{
		if(m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	//-------------------------------------
	//プレイヤーの数を返す

	unsigned int CharacterManager::GetCharacterNumber()const
	{
		return m_character.size();
	}

