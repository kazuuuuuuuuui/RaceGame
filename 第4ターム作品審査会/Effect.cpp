#include"Effect.h"
#include"Course.h"
#include"glut.h"

//-------------------------------------
//����̃R�[�X�̈�+������o�Ă��Ȃ����̔��f
//�o�Ă����ꍇ�񊈐��ɂ���

void Effect::checkCourseOut()
{
	if (m_basePosition.m_x < -100.f || m_basePosition.m_x > COURSE_WIDTH + 100.f)
	{
		m_isActive = false;
	}

	if (m_basePosition.m_z > 100.f || m_basePosition.m_z < -COURSE_HEIGHT-100.f)
	{
		m_isActive = false;
	}
}


