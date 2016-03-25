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

	ItemManager();
	static ItemManager* GetInstance();
	
};


#endif