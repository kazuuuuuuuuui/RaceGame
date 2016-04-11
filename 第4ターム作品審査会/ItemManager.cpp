#include"ItemManager.h"

//-------------------------------------
//コンストラクタ

ItemManager::ItemManager()
{
	//debug
	printf("アイテムマネージャー生成\n");
	printf("\n");

	m_itemNum = 0;

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

//-------------------------------------
//自身がnullptrでない場合自分自身を破棄する

void ItemManager::Destory()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}