#include<list>
#include"Effect.h"
#include"Course.h"
#include"glut.h"

//エフェクトを管理するlist
std::list<Effect*>effect;

//-------------------------------------
//既定のコース領域+αから出ていないかの判断
//出ていた場合非活性にする

void Effect::checkCourseOut(){

	if (m_basePosition.x < -100.f || m_basePosition.x > COURSE_WIDTH + 100.f){

		m_isActive = false;

	}



	if (m_basePosition.z > 100.f || m_basePosition.z < -COURSE_HEIGHT-100.f){

		m_isActive = false;

	}
}




GLuint EffectBlizzard = 0;

