//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include<stdio.h>
#include<stdlib.h>
#include"Camera.h"
#include"GameManager.h"
#include"joysticManager.h"
#include"ImageManager.h"
#include"SoundManager.h"
#include"CharacterManager.h"
#include"Sound.h"
#include"controller.h"
#include"glut.h"

//-------------------------------------
//fps�v���p�ϐ��Ɗ֐�(debug�p)

int g_GLframe = 0; //�t���[����
int g_GLtimenow = 0;//�o�ߎ���
int g_GLtimebase = 0;//�v���J�n����

void fps()
{
	g_GLframe++;
	g_GLtimenow = glutGet(GLUT_ELAPSED_TIME);//�o�ߎ��Ԃ��擾

	if (g_GLtimenow - g_GLtimebase > 1000)      //�P�b�ȏソ������fps���o��
	{
		printf("fps:%f\r", g_GLframe*1000.0 / (g_GLtimenow - g_GLtimebase));
		g_GLtimebase = g_GLtimenow;//����Ԃ�ݒ�                
		g_GLframe = 0;//�t���[���������Z�b�g
	}
}

//----------------------------------------
//�X�V�ƕ`��

void display() 
{
	oka::JoysticManager::GetInstance()->Update();
	oka::GameManager::GetInstance()->Updata();
	
}

//----------------------------------------
//display�֐���60F�P�ʂōċA�I�ɌĂяo���֐�

void timer(int value) {

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	glutForceJoystickFunc();

}

int g_window_width = 900;
int g_window_height = 900;

//-------------------------------------
//��ʂ̔䗦���ς�������ɕ`��T�C�Y���Čv�Z����R�[���o�b�N�֐�

void reshape(int width, int height)
{
	g_window_width = width;
	g_window_height = height;

}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(g_window_width, g_window_height);
	glutCreateWindow("BikeRacing");
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);

	glutMainLoop();
}