#include<list>
#include"Effect.h"
#include"Course.h"
#include"glut.h"

//エフェクトを管理するlist
std::list<Effect*>effect;

//-------------------------------------
//既定のコース領域から出ていないかの判断
//出ていた場合非活性にする

void Effect::checkCourseOut(){

	if (m_basePosition.x < 0.f || m_basePosition.x > COURSE_WIDTH){

		m_isActive = false;

	}



	if (m_position.z > 0 || m_position.z < -COURSE_HEIGHT + 1){

		m_isActive = false;
	
	}
}




GLuint EffectBlizzard = 0;

