#include"ItemManager.h"

//-------------------------------------
//コンストラクタ

//キャラクターのモデルデータの読み込みを行い //後で書き換え

//マネージャー生成時にプレイヤーの数分
//キャラクターを管理するベクターに対してnewしてpushする

ItemManager::ItemManager()
{
	for (unsigned int i = 0; i < SET_ITEM_NUMBER; i++)
	{
		m_item.push_back(new Item());
	}

}

ItemManager* ItemManager::m_instance = nullptr;

//-------------------------------------
//シングルトンにするためインスタンスがない場合のみnewし
//既にインスタンスがある場合はそのインスタンスをそのまま返す

ItemManager* ItemManager::GetInstance()
{
	if (nullptr == m_instance)
	{
		m_instance = new ItemManager();
	}

	return m_instance;
}