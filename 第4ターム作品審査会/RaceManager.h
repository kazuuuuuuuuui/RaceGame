#ifndef RACEMANAGER_H_
#define RACEMANAGER_H_

#include"Vec3.h"
#include"Course.h"
#include"Character.h"

class RaceManager
{
public:
	Course *m_course;
	unsigned int m_bgm;
	bool m_raceStart;
	char m_rapMax[256];

	static RaceManager* GetInstance();
	void CountRaceStart();
	void PrintRaceStrart()const;
	bool IsRaceEnd()const;

	void CheckRanking(std::vector<Character*> _character);
	void SetRanking(std::vector<Character*> _character);

	//bool SortRanking(Character *_my, Character *_you);

private:
	RaceManager() :
	m_course(nullptr),
	m_bgm(0),
	m_raceStart(false)
	{
		sprintf_s(m_rapMax, "%d", 3);
	};

	~RaceManager() {};

	static RaceManager* m_instance;




};

#endif