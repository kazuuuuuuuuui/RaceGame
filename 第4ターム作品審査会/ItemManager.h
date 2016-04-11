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

	//�A�C�e���̓Y�����Ɏg��
	//��ŏ�������
	int m_itemNum;

	static ItemManager* GetInstance();
	static void Destory();
	
	ItemManager();

	~ItemManager()
	{
		//debug
		printf("�A�C�e���}�l�[�W���[�폜\n");
		printf("\n");
	}

};


#endif