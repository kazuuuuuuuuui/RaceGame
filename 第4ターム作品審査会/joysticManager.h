#pragma once

#include"controller.h"

class JoysticManager{
public:

	contoroller m_contoroller[4];

	int connectingNum();

	void update();

	static JoysticManager* getInstance();

private:
	static JoysticManager* m_instance;

	JoysticManager(){};

};
