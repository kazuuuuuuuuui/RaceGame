#ifndef COURSESELECTSCENE_H_
#define COURSESELECTSCENE_H_

#include"BaseScene.h"
#include"Course.h"

class CourseSelectScene :public BaseScene
{
public:


	//-------------
	//�R�[�X�̎��

	enum CourseName
	{
		Course1 = 0,
		Course2,
		CourseNameMax
	};

	int m_selectedCourse;
	
	float m_rot;//�X�e�[�W�̃J�����A���O���Ɏg�p(�ύX�\��)

	Course *m_course[CourseNameMax];

	void Update();
	void Render();

	CourseSelectScene();
	~CourseSelectScene()
	{
		//debug
		printf("�R�[�X�I���V�[���폜\n");
	}

};

#endif