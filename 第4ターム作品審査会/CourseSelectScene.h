#ifndef COURSESELECTSCENE_H_
#define COURSESELECTSCENE_H_

#include"BaseScene.h"
#include"Course.h"

class CourseSelectScene :public BaseScene
{
public:


	//-------------
	//コースの種類

	enum CourseName
	{
		Course1 = 0,
		Course2,
		CourseNameMax
	};

	int m_selectedCourse;
	
	float m_rot;//ステージのカメラアングルに使用(変更予定)

	Course *m_course[CourseNameMax];

	void Update();
	void Render();

	CourseSelectScene();
	~CourseSelectScene()
	{
		//debug
		printf("コース選択シーン削除\n");
	}

};

#endif