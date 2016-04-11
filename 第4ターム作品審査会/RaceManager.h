#ifndef RACEMANAGER_H_
#define RACEMANAGER_H_

#include"Vec3.h"
#include"Course.h"
#include"Character.h"

class RaceManager
{
public:
	Course *m_course;
	bool m_raceStart;
	int m_flame;
	int startCount;


	char m_rapMax[256];

	static RaceManager* GetInstance();
	static void Destory();

	void CountRaceStart();
	void PrintRaceStrart()const;
	bool IsRaceEnd()const;

	void CheckRanking(std::vector<Character*> _character);
	void SetRanking(std::vector<Character*> _character);

	//bool SortRanking(Character *_my, Character *_you);

private:
	RaceManager() :
	m_course(nullptr),
	m_flame(0),
	startCount(6),
	m_raceStart(false)
	{
		//debug
		printf("\n");
		printf("���[�X�}�l�[�W���[����\n");
		printf("\n");

		oka::SoundManager::GetInstance()->AddSound("CountDown", oka::Sound::LoadSquareWave(count_sound, sizeof(count_sound), 440));

		sprintf_s(m_rapMax, "%d", 3);
	};

	~RaceManager()
	{
		printf("���[�X�}�l�[�W���[�폜\n");
		printf("\n");

		delete m_course;//nullptr�`�F�b�N�K�v����
		oka::SoundManager::GetInstance()->DeleteSound("CountDown");
	};

	static RaceManager* m_instance;




};

#endif