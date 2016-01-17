/*openGL�`��܂łɕK�v�ȏ�������*/

#define WINDOW_WIDTH (900)
#define WINDOW_HEIGHT (900)

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<time.h>
#include"camera.h"
#include"player.h"
#include"Course.h"
#include"MagicStone.h"
#include"StrokeString.h"
#include"FireEffect.h"
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

	if (' ' == key){
		glm::vec3 accelIncrement(-0.015*sin(player->m_rotate.y), 0, -0.015*cos(player->m_rotate.y));
		player->m_accel = accelIncrement;
	}
	else{
		player->m_accel = { 0.f, 0.f, 0.f };
	}

}


void specialkeydown(int key, int x, int y){

	if (GLUT_KEY_LEFT == key){
		player->m_rotate.y += 0.02f;
	}

	if (GLUT_KEY_RIGHT == key){
		player->m_rotate.y -= 0.02f;
	}

}

GLuint hoge = 0;

//-------------------------------------
//�Q�[���̏������S�ʂ��s��

void init(){

	srand(time(NULL));

	player = new Player();
	xFile::loadXfile("xFile/testbike.x", player->m_boby);
	xFile::loadXfile("xFile/taiya.x", player->m_backWheel);

	camera = new Camera();

	//��ŏ�������
	testCourse = new Course();

	for (int i = 0; i < SET_MAGICSTONE_NUMBER; i++){
		magicStone[i] = new MagicStone();
	}

	for (int i = 0; i < PARTICLE_NUNBER; i++){
		fire[i] = new FireEffect();
	}


	//�e�N�X�`���̓ǂݍ���
	//���ߓx����
	testCourse->m_handle[COUSE_TEXTURE] = BmpImage::loadImage("bmp/course1.bmp");
	testCourse->m_handle[BACKGROUND_TEXTURE] = BmpImage::loadImage("bmp/background1.bmp");

	//���ߓx�L��
	smoke_handle = BmpImage::loadImage_alpha("bmp/smoke.bmp");
	
	hoge = BmpImage::loadImage_alpha("bmp/piyo.bmp");

	//�R�[�X�f�[�^�̃o�b�t�@�쐬
	BmpImage::makeBuffer("bmp/buffer1.bmp", testCourse->m_buffer);

	//���΂̔z�u
	testCourse->setMagicStone();

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
unsigned int downkeys = 0;

void joystick(unsigned int buttonMask, int x, int y, int z){
	//printf("buttonMask:%u, x:%d ,y:%d z:%d\n", buttonMask, x, y, z);
	pressedKeys = buttonMask;
	releasedKeys = ~pressedKeys;
	changedKeys = pressedKeys ^ lastkeys;
	downkeys = pressedKeys & changedKeys;

	//-1000�`1000�̒l��-1�`1�̒l�ɕϊ����Ĉ����Ƃ��ēn��
	player->control(pressedKeys, downkeys, (float)x / 1000.f, (float)y / 1000.f, (float)z / 1000.f);

	lastkeys = buttonMask;
}

//��芸����
int flame = 0;
int milliSecond = 0;
int second = 0;
int minute = 0;

//���ԕ\���Ɏg��
char str_time[256];

//���񐔕\���Ɏg��
char str_lapCount[256];
char str_lapMax[256];

int getMilliSecond(int _flame){
	return ((_flame * 1000) / 60) % 1000;
}

int getSecond(int _flame){
	return _flame / 60;
}

int getMinute(int _second){
	return _second / 60;
}




//----------------------------------------
//�X�V�ƕ`��

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor(77.f / 255.f, 180.f / 255.f, 232.f / 255.f, 1);

	//�[�x�e�X�g
	glEnable(GL_DEPTH_TEST);

	//���C�g
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//���t���[��
	sprintf(str_lapCount, "%d", player->m_lapCount);
	sprintf(str_time, "%02d:%02d:%03d", minute, second, milliSecond);

	//�R�[�X�I������1�񂾂�
	sprintf(str_lapMax, "%d", LAP_MAX);

	/*�X�V*/
	flame++;

	//�~���b
	milliSecond = getMilliSecond(flame);

	//�b
	second = getSecond(flame);

	//��
	minute = getMinute(second);

	second = second % 60;


	camera->update(TYPE_3D);
	player->update();

	for (int i = 0; i < SET_MAGICSTONE_NUMBER; i++){
		magicStone[i]->update();
	}

	for (int i = 0; i < PARTICLE_NUNBER; i++){
		fire[i]->update();
	}

	/*�`��(3D)*/
	testCourse->draw();

	player->draw();

	glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);


	for (int i = 0; i < SET_MAGICSTONE_NUMBER; i++){
		magicStone[i]->draw();
	}

	for (int i = 0; i < PARTICLE_NUNBER; i++){
		fire[i]->draw();
	}
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, hoge);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glTranslatef(20, 0.001f, -180);
	glRotatef(90, 1, 0, 0);


	glBegin(GL_QUADS);
	glColor4f(1, 1, 1, 1);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0.f, 0.f);
	glVertex2f(-1.f, -1.f);
	glTexCoord2f(0.f, 1.f);
	glVertex2f(-1.f, 1.f);
	glTexCoord2f(1.f, 1.f);
	glVertex2f(1.f, 1.f);
	glTexCoord2f(1.f, 0.f);
	glVertex2f(1.f, -1.f);


	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);


	glPopMatrix();
	

	/*�X�V*/
	camera->update(TYPE_2D);



	/*�`��(2D)*/

	//����J�E���g�̕\��
	//�������̏o�͂�1�̊֐��ɂ܂Ƃ߂�\��

	if (false == player->m_isGoal){
		StrokeString::print("LAP", { 230, 250, 0 }, 0.1f, { 1, 0, 0 });
		StrokeString::print(str_lapCount, { 260, 250, 0 }, 0.18f, { 1, 0, 0 });
		StrokeString::print("/", { 275, 250, 0 }, 0.1f, { 1, 0, 0 });
		StrokeString::print(str_lapMax, { 285, 250, 0 }, 0.1f, { 1, 0, 0 });
		StrokeString::print("TIME", { 180, 280, 0 }, 0.13f, { 1, 0, 0 });
		StrokeString::print(str_time, { 220, 280, 0 }, 0.13f, { 1, 0, 0 });

		StrokeString::print("LAP1", { 220, 230, 0 }, 0.08f, { 1, 0, 0 });
		StrokeString::print(player->m_str_lapTime[FIRST], { 250, 230, 0 }, 0.08f, { 1, 0, 0 });

		StrokeString::print("LAP2", { 220, 215, 0 }, 0.08f, { 1, 0, 0 });
		StrokeString::print(player->m_str_lapTime[SECOND], { 250, 215, 0 }, 0.08f, { 1, 0, 0 });

		StrokeString::print("LAP3", { 220, 200, 0 }, 0.08f, { 1, 0, 0 });
		StrokeString::print(player->m_str_lapTime[THIRD], { 250, 200, 0 }, 0.08f, { 1, 0, 0 });

	}
	else{
		StrokeString::print("GOAL", { 75, 210, 0 }, 0.5f, { 1, 1, 1 });
	}

	glFlush();
}


//----------------------------------------
//display�֐���60F�P�ʂōċA�I�ɌĂяo���֐�

void timer(int value) {

	//printf("size:%d\n", player->m_hasMagicStone.size());

	//system("cls");

	//printf("%f %f\n", magicStone->m_position.x, magicStone->m_position.z);
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
	glutSpecialFunc(specialkeydown);

	init();//�Q�[���̏�����

	glutMainLoop();
}