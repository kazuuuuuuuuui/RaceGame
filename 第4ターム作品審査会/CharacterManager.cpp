#include"CharacterManager.h"
#include"xFile.h"

	//-------------------------------------
	//コンストラクタ

	//キャラクターのモデルデータの読み込みを行い //後で書き換え
	
	//マネージャー生成時にプレイヤーの数分
	//キャラクターを管理するベクターに対してnewしてpushする

	CharacterManager::CharacterManager()
	{
		xFile body;
		xFile wheel;

		//モデルデータの読み込み
		xFile::loadXfile("xFile/bike.x", body);
		xFile::loadXfile("xFile/taiya.x", wheel);

		//車体のモデルデータの向き修正
		body.rotate();

		for (int i = 0; i < PLAYER_MAX_NUMBER; i++)
		{
			m_character.push_back(new Character(body, wheel));
		}
	}
	
	
	CharacterManager* CharacterManager::m_instance = nullptr;

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
	//プレイヤーの数を返す

	unsigned int CharacterManager::GetCharacterNumber()const
	{
		return m_character.size();
	}

