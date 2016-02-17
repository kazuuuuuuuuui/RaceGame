
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#include<stdio.h>
#include<stdlib.h>
#include"GameManager.h"
#include"joysticManager.h"
#include"Sound.h"
#include"controller.h"
#include"glut.h"








//-------------------------------------
//fps�v���p�ϐ��Ɗ֐�(debug�p)

int g_GLframe = 0; //�t���[����
int g_GLtimenow = 0;//�o�ߎ���
int g_GLtimebase = 0;//�v���J�n����

void fps(){
	g_GLframe++;
	g_GLtimenow = glutGet(GLUT_ELAPSED_TIME);//�o�ߎ��Ԃ��擾

	if (g_GLtimenow - g_GLtimebase > 1000)      //�P�b�ȏソ������fps���o��
	{
		printf("fps:%f\r", g_GLframe*1000.0 / (g_GLtimenow - g_GLtimebase));
		g_GLtimebase = g_GLtimenow;//����Ԃ�ݒ�                
		g_GLframe = 0;//�t���[���������Z�b�g
	}
}


//-------------------------------------
//�L�[�{�[�h����̓��͑S��

void keyboard(unsigned char key, int x, int y){


}

//----------------------------------------
//�X�V�ƕ`��

void display() {

	GameManager::getInstance()->updata();


}

int flame = 0;

//----------------------------------------
//display�֐���60F�P�ʂōċA�I�ɌĂяo���֐�

void timer(int value) {

	flame++;

	JoysticManager::getInstance()->update();

	//for (int i = 0; i < 4; i++){

	//	if (JoysticManager::getInstance()->m_contoroller[i].m_isConnect){
	//		printf("[%d]:�ڑ�����Ă܂�", i);
	//	}
	//	else{
	//		printf("[%d]:�ڑ�����Ă܂���", i);
	//	}

	//	if (i == 3){ printf("\n"); }

	//}

	//printf("%f %f\n", xx, yy);

	//printf("x:%f z:%f\n", player->m_position.x, player->m_position.z);

	fps();

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	glutForceJoystickFunc();

}

int window_width = 900;
int window_height = 900;

//-------------------------------------
//��ʂ̔䗦���ς�������ɕ`��T�C�Y���Čv�Z����R�[���o�b�N�֐�

void reshape(int width, int height)
{
	window_width = width;
	window_height = height;

}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("��4�^�[����i�R����");

	Sound::init();

	JoysticManager::getInstance();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}