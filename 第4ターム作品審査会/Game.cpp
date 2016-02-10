#include<stdio.h>
#include<stdlib.h>
#include<vector>
#define _USE_MATH_DEFINES
#include<math.h>
#include<time.h>
#include<algorithm>
#include<list>
#include"GameManager.h"
#include"camera.h"
#include"Item.h"
#include"Effect.h"
#include"Dash.h"
#include"Smoke.h"
#include"moji.h"
#include"joysticManager.h"
#include"Sound.h"
#include"controller.h"
#include"glut.h"

int window_width = 900;
int window_height = 900;

//debug
float xx = 0.f;
float yy = 0.f;

//-------------------------------------
//fps�v���p�ϐ��Ɗ֐�
int GLframe = 0; //�t���[����
int GLtimenow = 0;//�o�ߎ���
int GLtimebase = 0;//�v���J�n����

void fps(){
	GLframe++; //�t���[�������{�P
	GLtimenow = glutGet(GLUT_ELAPSED_TIME);//�o�ߎ��Ԃ��擾

	if (GLtimenow - GLtimebase > 1000)      //�P�b�ȏソ������fps���o��
	{
		printf("fps:%f\r", GLframe*1000.0 / (GLtimenow - GLtimebase));
		GLtimebase = GLtimenow;//����Ԃ�ݒ�                
		GLframe = 0;//�t���[���������Z�b�g
	}
}

//-------------------------------------



//-------------------------------------
//�L�[�{�[�h����̓��͑S��

void keyboard(unsigned char key, int x, int y){

	//debug
	if ('d' == key){

		xx += 1.f;
	}
	else if ('a' == key){

		xx -= 1.f;
	}
	else if ('w' == key){

		yy += 1.f;
	}
	else if ('s' == key){

		yy -= 1.f;
	}



}

//-------------------------------------
//�v���C���[�̐���
//unsigned int pressedKeys = 0;//���t���[��������Ă���L�[
//unsigned int lastkeys = 0;//�O�t���[���O�ɉ�����Ă����L�[
//unsigned int changedKeys = 0;//�O�t���[���ƌ��t���[���ŕω����������L�[
//unsigned int downkeys = 0;

void joystick(unsigned int buttonMask, int x, int y, int z){

	//printf("buttonMask:%u, x:%d ,y:%d z:%d\n", buttonMask, x, y, z);
	//pressedKeys = buttonMask;
	//changedKeys = pressedKeys ^ lastkeys;
	//downkeys = pressedKeys & changedKeys;

	//JoysticManager::getInstance()->m_buttonMask = pressedKeys;
	//JoysticManager::getInstance()->m_downKey = downkeys;

	////-1000�`1000�̒l��-1�`1�̒l�ɕϊ����ēn��
	//JoysticManager::getInstance()->m_x = (float)x / 1000.f;
	//JoysticManager::getInstance()->m_y = (float)y / 1000.f;
	//JoysticManager::getInstance()->m_z = (float)z / 1000.f;

	//lastkeys = buttonMask;
}


//----------------------------------------
//�X�V�ƕ`��

void display() {

	GameManager::getInstance()->updata();


}


//----------------------------------------
//display�֐���60F�P�ʂōċA�I�ɌĂяo���֐�

void timer(int value) {

	JoysticManager::getInstance()->update();

	//printf("%f %f\n", xx, yy);

	//printf("x:%f z:%f\n", player->m_position.x, player->m_position.z);

	fps();

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	glutForceJoystickFunc();

}


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
	glutJoystickFunc(joystick, 0);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
}