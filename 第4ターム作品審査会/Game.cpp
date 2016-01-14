/*openGL�`��܂łɕK�v�ȏ�������*/

#define WINDOW_WIDTH (900)
#define WINDOW_HEIGHT (900)

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"camera.h"
#include"player.h"
#include"Course.h"
#include"MagicStone.h"
#include"StrokeString.h"
#include"glut.h"

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
//�L�[�{�[�h����̓��͑S��

void keyboard(unsigned char key, int x, int y){



}
//
//
//void specialkeydown(int key, int x, int y){
//
//
//
//}

//-------------------------------------
//�Q�[���̏������S�ʂ��s��

void init(){

	player = new Player();
	xFile::loadXfile("xFile/testbike.x",player->m_boby);

	camera = new Camera();

	//��ŏ�������
	testCourse = new Course();

	//�e�N�X�`���̓ǂݍ���
	testCourse->m_handle[COUSE_TEXTURE] = BmpImage::loadImage("bmp/course1.bmp");
	testCourse->m_handle[BACKGROUND_TEXTURE] = BmpImage::loadImage("bmp/background1.bmp");

	//�R�[�X�f�[�^�̃o�b�t�@�쐬
	BmpImage::makeBuffer("bmp/buffer1.bmp", testCourse->m_buffer);

	magicStone = new MagicStone();

	//�g�p���閂�΂̃e�N�X�`���ǂݍ���
	fire_handle = BmpImage::loadImage("bmp/fire.bmp");
	blizzard_handle = BmpImage::loadImage("bmp/blizzard.bmp");
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

//��芸����
int flame = 0;
int decimal = 0;
int second = 0;
int minute = 0;

char str_time[256];

char str_lapCount[256];
char str_lapMax[256];



//----------------------------------------
//�X�V�ƕ`��

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(77.f / 255.f, 180.f / 255.f, 232.f / 255.f, 1);

	//�[�x�e�X�g
	glEnable(GL_DEPTH_TEST);

	//���C�g
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	//���t���[��
	sprintf(str_lapCount, "%d", player->m_lapCount);
	sprintf(str_time, "%02d:%02d:%03d", minute, second, decimal);


	//�R�[�X�I������1�񂾂�
	sprintf(str_lapMax, "%d", LAP_MAX);


	/*�X�V*/
	camera->update(TYPE_3D);
	player->update();

	/*�`��(3D)*/
	testCourse->draw();

	magicStone->draw();

	player->draw();

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);


	/*�X�V*/
	camera->update(TYPE_2D);

	flame++;

	//�~���b
	decimal = ((flame * 1000) / 60) % 1000;

	second = flame / 60;

	minute = second / 60;

	second = second % 60;


	/*�`��(2D)*/

	//����J�E���g�̕\��
	//�������̏o�͂�1�̊֐��ɂ܂Ƃ߂�\��
	StrokeString::print("LAP", { 230, 250, 0 }, 0.1f, { 1, 0, 0 });
	StrokeString::print(str_lapCount, { 260, 250, 0 }, 0.18f, { 1, 0, 0 });
	StrokeString::print("/", { 275, 250, 0 }, 0.1f, { 1, 0, 0 });
	StrokeString::print(str_lapMax, { 285, 250, 0 }, 0.1f, { 1, 0, 0 });
	StrokeString::print("TIME", { 180, 280, 0 }, 0.13f, { 1, 0, 0 });

	StrokeString::print(str_time, { 220, 280, 0 }, 0.13f, { 1, 0, 0 });

	glFlush();
}


//----------------------------------------
//display�֐���60F�P�ʂōċA�I�ɌĂяo���֐�

void timer(int value) {
	//system("cls");

	//printf("%f %f", player->m_position.x, player->m_position.z);
	//printf(" %d\n", testCourse->m_buffer[COURSE_HEIGHT - 1 + (int)player->m_position.z][(int)player->m_position.x]);

	//printf("CheckPoint:%d\n", player->m_checkFlag);
	//printf("LAP:%d\n", player->m_lapCount);


	fps();

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
	glutKeyboardFunc(keyboard);
	//glutSpecialFunc(specialkeydown);

	init();//�Q�[���̏�����

	glutMainLoop();
}