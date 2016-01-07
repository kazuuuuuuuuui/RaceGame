/*openGL�`��܂łɕK�v�ȏ�������*/

#define WINDOW_WIDTH (900)
#define WINDOW_HEIGHT (900)

#include<stdio.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"camera.h"
#include"player.h"
#include"Course.h"
#include"MagicStone.h"
#include"glut.h"

Camera *camera = nullptr;

//debug

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
//�Q�[���̏������S�ʂ��s��

void init(){

	player = new Player();
	camera = new Camera();

	//��ŏ�������
	testCourse = new Course();
	testCourse->m_handle = BmpImage::loadImage("bmp/testCourse.bmp");

	magicStone = new MagicStone();

	fire_handle = BmpImage::loadImage("bmp/fire.bmp");
}


//-------------------------------------
//�v���C���[�̐���
unsigned int pressedKeys = 0;//���t���[��������Ă���L�[
unsigned int releasedKeys = 0;//���t���[��������Ă��Ȃ��L�[
unsigned int lastkeys = 0;//�O�t���[���O�ɉ�����Ă����L�[
unsigned int changedKeys = 0;//�O�t���[���ƌ��t���[���ŕω����������L�[

void joystick(unsigned int buttonMask, int x, int y, int z){
	//printf("buttonMask:%u, x:%d ,y:%d z:%d\n", buttonMask, x, y, z);
	pressedKeys = buttonMask;
	releasedKeys = ~pressedKeys;
	changedKeys = pressedKeys ^ lastkeys;

	//-1000�`1000�̒l��-1�`1�̒l�ɕϊ����Ĉ����Ƃ��ēn��
	player->control(pressedKeys, (float)x / 1000.f, (float)y / 1000.f, (float)z / 1000.f);

	lastkeys = buttonMask;
}


//----------------------------------------
//�X�V�ƕ`��

void display() {
	/*�X�V*/
	camera->update();
	player->update();






	/*�`��*/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�[�x�e�X�g
	glEnable(GL_DEPTH_TEST);

	testCourse->draw();

	magicStone->draw();

	player->draw();

	glDisable(GL_DEPTH_TEST);

	glFlush();
}


//----------------------------------------
//display�֐���60F�P�ʂōċA�I�ɌĂяo���֐�

void timer(int value) {
	system("cls");

	//printf("%d %d %d \n", pix->r, pix->g, pix->b);
	//printf("%f %f", camera->m_position.x, camera->m_position.z);

	//fps();

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	glutForceJoystickFunc();

}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("��4�^�[����i�R����");

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutJoystickFunc(joystick, 0);

	init();//�Q�[���̏�����

	glutMainLoop();
}