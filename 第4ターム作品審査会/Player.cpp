#define BUTTON_A (1)
#define BUTTON_X (4)

#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>
#include"Course.h"
#include"player.h"
#include"glut.h"

Player *player = nullptr;

//-------------------------------------
//自機の更新

void Player::update(){

	m_speed += m_accel;
	m_position += m_speed;

	//減速させる慣性
	m_speed *= 0.965f;

}


//-------------------------------------
//自機の描画

void Player::draw(){
	glPushMatrix();
	{
		/*自機操作*/
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(m_rotate.y * 180 / M_PI, 0, 1, 0);
		glScalef(m_scale.x, m_scale.y, m_scale.z);

		glColor3f(0, 1, 0);
		glBegin(GL_TRIANGLES);
		{
			glVertex3f(0, 0, -1.5);
			glVertex3f(-0.5, 0, 1);
			glVertex3f(0.5, 0, 1);
		}
		glEnd();

	}
	glPopMatrix();
}

//-------------------------------------
//自機の制御

void Player::control(unsigned int _key, float _x, float _y, float _z){

	//前進(Aボタン)
	if (_key & BUTTON_A){

		//加速度の設定
		//-0.005fは補正値
		glm::vec3 accelIncrement(-0.01*sin(m_rotate.y), 0, -0.01*cos(m_rotate.y));
		m_accel = accelIncrement;
	}
	else{
		m_accel = { 0.f, 0.f, 0.f };
	}

	//後退(xボタン)
	/*if (_key & BUTTON_X){
		m_speed.z = 0.1f;
		}*/

	//正面右に移動
	if ((_key & BUTTON_A || _key & BUTTON_X) && _x > 0.9){
		m_rotate.y -= 0.02f;
	}

	//正面左に移動
	//0.05fは補正値
	if ((_key & BUTTON_A || _key & BUTTON_X) && _x < -0.9){
		m_rotate.y += 0.02f;
	}

}

//-------------------------------------
//プレイヤーがダートに入っているか判定
//入っていたらtrue 入っていなかったらfalseを返す

bool Player::inDart(){
	/*if (testCourse->){
		return true;
	}
	else{
		return false;
	}*/
	return false;
}



