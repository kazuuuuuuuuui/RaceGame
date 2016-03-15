#include<list>
#include"Effect.h"
#include"Course.h"
#include"glut.h"

GLuint smoke_handle = 0;

//エフェクトを管理するlist
std::list<Effect*>effect;

//-------------------------------------
//既定のコース領域+αから出ていないかの判断
//出ていた場合非活性にする

void Effect::checkCourseOut(){

	if (m_basePosition.m_x < -100.f || m_basePosition.m_x > COURSE_WIDTH + 100.f){

		m_isActive = false;

	}



	if (m_basePosition.m_z > 100.f || m_basePosition.m_z < -COURSE_HEIGHT-100.f){

		m_isActive = false;

	}
}




GLuint EffectBlizzard = 0;

