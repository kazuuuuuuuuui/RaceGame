#include<list>
#include"Effect.h"
#include"Course.h"
#include"glut.h"

//�G�t�F�N�g���Ǘ�����list
std::list<Effect*>effect;

//-------------------------------------
//����̃R�[�X�̈悩��o�Ă��Ȃ����̔��f
//�o�Ă����ꍇ�񊈐��ɂ���

//void Effect::checkCourseOut(){
//
//	if (m_basePosition.x < 0.f || m_basePosition.x > COURSE_WIDTH){
//
//		m_isActive = false;
//
//	}
//
//
//
//	if (m_position.z > 0 || m_position.z < -COURSE_HEIGHT + 1){
//
//		m_isActive = false;
//	
//	}
//}




GLuint EffectBlizzard = 0;

