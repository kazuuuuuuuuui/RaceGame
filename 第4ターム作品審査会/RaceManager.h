#ifndef RACEMANAGER_H_
#define RACEMANAGER_H_

#include"Course.h"
#include"Character.h"

class RaceManager
{
public:
	Course *m_course;
	bool m_raceStart;	//レースが始まっているかのフラグ
	unsigned int m_bgm;

	static RaceManager* GetInstance();
	void CountRaceStart();
	void PrintRaceStrart()const;

	void CheckRanking(std::vector<Character*> _character);
	void SetRanking(std::vector<Character*> _character);
	//bool SortRanking(Character *_my, Character *_you);

private:
	RaceManager() :
	m_course(nullptr),
	m_raceStart(false),
	m_bgm(0)
	{};

	~RaceManager() {};

	static RaceManager* m_instance;




};

#endif