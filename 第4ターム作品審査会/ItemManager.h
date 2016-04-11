#ifndef ITEMMANAGER_H_
#define ITEMMANAGER_H_

#include<vector>
#include"Item.h"

class ItemManager
{
private:
	static ItemManager* m_instance;

public:
	std::vector<Item*> m_item;

	//アイテムの添え字に使う
	//後で書き換え
	int m_itemNum;

	static ItemManager* GetInstance();
	static void Destory();
	
	ItemManager();

	~ItemManager()
	{
		//debug
		printf("アイテムマネージャー削除\n");
		printf("\n");
	}

};


#endif