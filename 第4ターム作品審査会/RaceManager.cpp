#include<algorithm>
#include"RaceManager.h"
#include"CharacterManager.h"
#include"ImageManager.h"
#include"SoundManager.h"
#include"glut.h"

RaceManager* RaceManager::m_instance = nullptr;

//-----------------------------------------------------------
//シングルトンにするためインスタンスがない場合のみnewし
//既にインスタンスがある場合はそのインスタンスをそのまま返す

RaceManager* RaceManager::GetInstance()
{
	if (nullptr == m_instance)
	{
		m_instance = new RaceManager();
	}
	return m_instance;
}

//-------------------------------------
//自身がnullptrでない場合自分自身を破棄する

void RaceManager::Destory()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

//-------------------------------------
//レーススタートのカウントダウン

void RaceManager::CountRaceStart()
{
	m_flame++; //フレーム数を＋１

	if (0 == m_flame % 60)      //１秒以上たったら処理を行う
	{
		startCount--;

		if (0 == startCount) 
		{

			//カウントダウンが終了したら
			//レースが開始されているかのフラグを立てる
			m_raceStart = true;

		}
       
		m_flame = 0;//フレーム数をリセット
	}

	//カウントダウンの音
	if (3 == startCount && m_flame == 0)
	{
		oka::SoundManager::GetInstance()->Play("CountDown");
	}
	if (3 == startCount && m_flame == 30)
	{
		oka::SoundManager::GetInstance()->Stop("CountDown");
	}

	if (2 == startCount && m_flame == 0)
	{
		oka::SoundManager::GetInstance()->Play("CountDown");
	}
	if (2 == startCount && m_flame == 30)
	{
		oka::SoundManager::GetInstance()->Stop("CountDown");
	}

	if (1 == startCount && m_flame == 0)
	{
		oka::SoundManager::GetInstance()->Play("CountDown");
	}
	if (1 == startCount && m_flame == 30)
	{
		oka::SoundManager::GetInstance()->Stop("CountDown");
	}

	if (0 == startCount && m_flame == 0)
	{
		oka::SoundManager::GetInstance()->ChangePitch("CountDown", 2.0f);
		oka::SoundManager::GetInstance()->Play("CountDown");
	}

	if (-1 == startCount && m_flame == 10)
	{
		oka::SoundManager::GetInstance()->Stop("CountDown");
		oka::Sound::Play(RaceManager::GetInstance()->m_course->m_bgm);
	}

}

//-------------------------------------
//カウントダウン(３・２・１・Go)の描画

void RaceManager::PrintRaceStrart()const
{

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (startCount <= 3 && startCount > 0)
	{
		glPushMatrix();
		{
			glTranslatef(100, 100, 0);

			if (startCount == 3)
			{
				glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("CountDown3"));
			}
			else if (startCount == 2)
			{
				glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("CountDown2"));
			}
			else if (startCount == 1)
			{
				glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("CountDown1"));
			}

			glColor4f(1, 1, 1, 1);

			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex2f(0, 0);

				glTexCoord2f(1, 1);
				glVertex2f(100, 0);

				glTexCoord2f(1, 0);
				glVertex2f(100, 100);

				glTexCoord2f(0, 0);
				glVertex2f(0, 100);
			}
			glEnd();
		}
		glPopMatrix();

	}
	else if (0 == startCount) 
	{

		glPushMatrix();
		{
			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Go"));

			glTranslatef(150, 150, 0);
			
			glColor4f(1, 1, 1, 1);

			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex2f(-50, -50);

				glTexCoord2f(1, 1);
				glVertex2f(50, -50);

				glTexCoord2f(1, 0);
				glVertex2f(50, 50);

				glTexCoord2f(0, 0);
				glVertex2f(-50, 50);
			}
			glEnd();
		}
		glPopMatrix();

	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}


//-------------------------------------
//順位判定用関数
//周回数→チェックポイントの進み具合→目指している次のチェックポイントへの距離の
//順番に判定する

/*メンバ関数に出来ない(sort関数に渡せない)ので後日聞く*/


bool SortRanking(Character *_my, Character *_you)
{
	//周回数での判定
	if (_my->m_lapCount > _you->m_lapCount)
	{
		return true;
	}
	else if (_my->m_lapCount < _you->m_lapCount)
	{
		return false;
	}

	//チェックポイントの進み具合での判定
	if (_my->m_nowPoint > _you->m_nowPoint)
	{
		return true;
	}
	else if (_my->m_nowPoint < _you->m_nowPoint)
	{
		return false;
	}

	//目指しているチェックポイントへの距離での判定
	if (_my->m_nextCheckPointLength > _you->m_nextCheckPointLength)
	{
		return false;
	}
	else if (_my->m_nextCheckPointLength < _you->m_nextCheckPointLength)
	{
		return true;
	}

	//取り敢えず何か返す
	return false;

}


//-------------
//順位のソート
//

void RaceManager::CheckRanking(std::vector<Character*> _character)
{
	//順位の判定
	for (unsigned int i = 0; i < _character.size(); i++)
	{
		std::sort(_character.begin(), _character.end(), SortRanking);
	}

	SetRanking(_character);

}

//-----------
//順位の付与

void RaceManager::SetRanking(std::vector<Character*> _character)
{
	for (unsigned int i = 0; i < _character.size(); i++)
	{
		_character[i]->m_ranking = i + 1;
	}
}


//----------------------------------------------------------
//レースが終了しているかの判定を行う
//キャラクター全員のis_Goalフラグを参照し
//レースが終了していたらtrue 終了していなかったらfalseを返す

bool RaceManager::IsRaceEnd()const
{
	bool flag = true;//判別用フラグ

	for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++)
	{
		flag = flag & CharacterManager::GetInstance()->m_character[i]->m_isGoal;
	}

	if (flag)
	{
		return true;
	}
	else
	{
		return false;
	}

}