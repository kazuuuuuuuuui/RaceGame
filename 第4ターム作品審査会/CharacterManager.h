#ifndef CHARACTERMANAGER_H_
#define CHARACTERMANAGER_H_

#include<vector>
#include"Character.h"

class CharacterManager
{
private:
	static CharacterManager* m_instance;

public:
	std::vector<Character*> m_character;

	CharacterManager();
	static CharacterManager* GetInstance();
	unsigned int GetCharacterNumber()const;
};


#endif