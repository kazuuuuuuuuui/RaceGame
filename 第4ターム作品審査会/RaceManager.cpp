#include<algorithm>
#include"RaceManager.h"
#include"CharacterManager.h"
#include"ImageManager.h"
#include"SoundManager.h"
#include"glut.h"

RaceManager* RaceManager::m_instance = nullptr;

//-----------------------------------------------------------
//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�

RaceManager* RaceManager::GetInstance()
{
	if (nullptr == m_instance)
	{
		m_instance = new RaceManager();
	}
	return m_instance;
}

//-------------------------------------
//���g��nullptr�łȂ��ꍇ�������g��j������

void RaceManager::Destory()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}

//-------------------------------------
//���[�X�X�^�[�g�̃J�E���g�_�E��

void RaceManager::CountRaceStart()
{
	m_flame++; //�t���[�������{�P

	if (0 == m_flame % 60)      //�P�b�ȏソ�����珈�����s��
	{
		startCount--;

		if (0 == startCount) 
		{

			//�J�E���g�_�E�����I��������
			//���[�X���J�n����Ă��邩�̃t���O�𗧂Ă�
			m_raceStart = true;

		}
       
		m_flame = 0;//�t���[���������Z�b�g
	}

	//�J�E���g�_�E���̉�
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
//�J�E���g�_�E��(�R�E�Q�E�P�EGo)�̕`��

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
//���ʔ���p�֐�
//���񐔁��`�F�b�N�|�C���g�̐i�݋���ڎw���Ă��鎟�̃`�F�b�N�|�C���g�ւ̋�����
//���Ԃɔ��肷��

/*�����o�֐��ɏo���Ȃ�(sort�֐��ɓn���Ȃ�)�̂Ō������*/


bool SortRanking(Character *_my, Character *_you)
{
	//���񐔂ł̔���
	if (_my->m_lapCount > _you->m_lapCount)
	{
		return true;
	}
	else if (_my->m_lapCount < _you->m_lapCount)
	{
		return false;
	}

	//�`�F�b�N�|�C���g�̐i�݋�ł̔���
	if (_my->m_nowPoint > _you->m_nowPoint)
	{
		return true;
	}
	else if (_my->m_nowPoint < _you->m_nowPoint)
	{
		return false;
	}

	//�ڎw���Ă���`�F�b�N�|�C���g�ւ̋����ł̔���
	if (_my->m_nextCheckPointLength > _you->m_nextCheckPointLength)
	{
		return false;
	}
	else if (_my->m_nextCheckPointLength < _you->m_nextCheckPointLength)
	{
		return true;
	}

	//��芸���������Ԃ�
	return false;

}


//-------------
//���ʂ̃\�[�g
//

void RaceManager::CheckRanking(std::vector<Character*> _character)
{
	//���ʂ̔���
	for (unsigned int i = 0; i < _character.size(); i++)
	{
		std::sort(_character.begin(), _character.end(), SortRanking);
	}

	SetRanking(_character);

}

//-----------
//���ʂ̕t�^

void RaceManager::SetRanking(std::vector<Character*> _character)
{
	for (unsigned int i = 0; i < _character.size(); i++)
	{
		_character[i]->m_ranking = i + 1;
	}
}


//----------------------------------------------------------
//���[�X���I�����Ă��邩�̔�����s��
//�L�����N�^�[�S����is_Goal�t���O���Q�Ƃ�
//���[�X���I�����Ă�����true �I�����Ă��Ȃ�������false��Ԃ�

bool RaceManager::IsRaceEnd()const
{
	bool flag = true;//���ʗp�t���O

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