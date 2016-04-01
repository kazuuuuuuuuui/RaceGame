#ifndef COURSESELECTSCENE_H_
#define COURSESELECTSCENE_H_

#include"BaseScene.h"

class CourseSelectScene :public BaseScene
{
public:


	//-------------
	//ÉRÅ[ÉXÇÃéÌóﬁ

	enum CourseName
	{
		Course1 = 0,
		Course2,
		Max
	};

	int m_selectedCourse;

	void Update();
	void Render();

	CourseSelectScene():
	m_selectedCourse(Course1)
	{}

};

#endif