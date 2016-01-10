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
	if (getMagicStone()){}

	//ダートに入ったかの判定と処理
	if (inDart()){
		m_speed *= 0.9f;
	}

	//チェックポイントを順送で通過したかの判定
	if (passCheckPoint()){
		m_checkFlag = true;
	}

	//1周したかの判定
	if (countLap()){
		m_lapCount++;
		m_checkFlag = false;
	}

	//ゴールしたかの判定
	if (isGoal()){
		exit(1);
	}

}


//-------------------------------------
//自機の描画

void Player::draw(){
	glPushMatrix();
	{
		/*自機操作*/
		glTranslatef(m_position.x, m_position.y, m_position.z);

		/*glRotatef(90, 1, 0, 0);
		glRotatef(180, 0, 1, 0);
		glRotatef(m_rotate.y * 180 / M_PI, 0, 1, 0);

		glScalef(m_scale.x, m_scale.y, m_scale.z);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		std::vector<float>::iterator itr_v = m_vertex.begin();
		glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

		std::vector<float>::iterator itr_n = m_normal.begin();
		glNormalPointer(GL_FLOAT, 0, &(*itr_n));

		std::vector<unsigned short>::iterator itr_i = m_index.begin();

		glDrawElements(GL_TRIANGLES, m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));*/

		glColor3f(1, 0, 0);
		glutWireCube(1);

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

	//プレイヤーがどのピクセル上にいるか判断し
	//直下のピクセル情報によって判定する

	if (testCourse->m_buffer[COURSE_HEIGHT - 1 + (int)m_position.z][(int)m_position.x] == DART){

		return true;

	}
	else{

		return false;

	}
}

//-------------------------------------
//プレイヤーが順走してチェックポイントを
//通過したかどうかの判定を行う
//チェックポイントの手前に位置していたらnumに1
//チェックポイントの直後に位置していたらnumに2
//それ以外は0を代入し、numの値が1→2に変化したときのみtrueを返す

bool Player::passCheckPoint(){

	//チェックポイントを順送して
	//通過したかどうがを判定するための使い捨てstatic変数
	static int num = 0;

	if (testCourse->m_buffer[COURSE_HEIGHT - 1 + (int)m_position.z][(int)m_position.x] == CHECK_FLONT){

		num = 1;

	}

	else if (testCourse->m_buffer[COURSE_HEIGHT - 1 + (int)m_position.z][(int)m_position.x] == CHECK_BEHIND){
		if (1 == num){
			num = 2;
			return true;
		}
		else{
			num = 2;
		}
	}

	else{
		num = 0;
	}

	return false;
}

//-------------------------------------
//プレイヤーがコースを順走して1周したかどうかの判定を行う
//ゴールの位置にいるときにチェックポイントを通過しているか判別する
//フラグがtrueの状態のときのみtrueを返し1周とカウントする

bool Player::countLap(){

	if (testCourse->m_buffer[COURSE_HEIGHT - 1 + (int)m_position.z][(int)m_position.x] == GOAL && m_checkFlag == true){

		return true;

	}

	return false;

}

//-------------------------------------
//プレイヤーがゴールしたかの判定
//周回数が3になった時点でtrueを返しゴールとする

bool Player::isGoal(){

	if (LAP_MAX == m_lapCount){

		return true;

	}

	return false;

}