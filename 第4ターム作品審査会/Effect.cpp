#include<list>
#include"Effect.h"
#include"Course.h"
#include"glut.h"

//�G�t�F�N�g���Ǘ�����list
std::list<Effect*>effect;

//-------------------------------------
//����̃R�[�X�̈�+������o�Ă��Ȃ����̔��f
//�o�Ă����ꍇ�񊈐��ɂ���

void Effect::checkCourseOut(){

	if (m_basePosition.x < -100.f || m_basePosition.x > COURSE_WIDTH + 100.f){

		m_isActive = false;

	}



	if (m_basePosition.z > 100.f || m_basePosition.z < -COURSE_HEIGHT-100.f){

		m_isActive = false;

	}
}




GLuint EffectBlizzard = 0;

