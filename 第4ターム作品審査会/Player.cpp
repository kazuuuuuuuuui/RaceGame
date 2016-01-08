#define BUTTON_A (1)
#define BUTTON_X (4)

#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>
#include"Course.h"
#include"player.h"
#include"BmpImage.h"
#include"glut.h"

Player *player = nullptr;

//-------------------------------------
//自機の更新

void Player::update(){

	m_speed += m_accel;
	m_position += m_speed;

	//減速させる慣性
	m_speed *= 0.965f;

	//魔石をゲットしたかの判定と処理
	if (getMagicStone()){


	}

	inDart();

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

		/*glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		std::vector<float>::iterator itr_v = m_vertex.begin();
		glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

		std::vector<float>::iterator itr_n = m_normal.begin();
		glNormalPointer(GL_FLOAT, 0, &(*itr_n));

		std::vector<unsigned short>::iterator itr_i = m_index.begin();

		glDrawElements(GL_TRIANGLES, m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));*/

		

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
//プレイヤーが魔石をゲットしたかどうか判定
//ゲットしていたらtrue ゲットしていなかったらfalseを返す

bool Player::getMagicStone(){

	//プレイヤーと魔石との距離
	glm::vec3 distance;
	distance.x = (magicStone->m_position.x - m_position.x);
	distance.y = (magicStone->m_position.y - m_position.y);
	distance.z = (magicStone->m_position.z - m_position.z);

	float length = sqrt(distance.x*distance.x + distance.y*distance.y + distance.z*distance.z);

	if (length < 1.f){
		return true;
	}
	else{
		return false;
	}

}

//-------------------------------------
//プレイヤーがダートに入っているか判定
//入っていたらtrue 入っていなかったらfalseを返す

bool Player::inDart(){

	

	return false;
}




