#define BUTTON_A (1)
#define BUTTON_X (4)
#define BUTTON_Y (8)
#define BUTTON_RB (16)

#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include<stdio.h>
#include<math.h>
#include"Course.h"
#include"player.h"
#include"camera.h"
#include"BmpImage.h"
#include"glut.h"

Player *player = nullptr;


//タイヤの位置等を後でいじる
//取り敢えず
extern int flame;
extern int milliSecond;
extern int second;
extern int minute;

int getMilliSecond(int _flame);
int getSecond(int _flame);
int getMinute(int _second);



//-------------------------------------
//自機の更新

void Player::update(){

	//printf("%02d::%02d::%03d\n", getMinute(getSecond(m_flame)), getSecond(m_flame), getMilliSecond(m_flame));

	//フレームの管理
	m_flame++;

	sprintf(m_str_lapTime[FIRST], "%02d:%02d:%03d ", m_minute[FIRST], m_second[FIRST], m_milliSecond[FIRST]);
	sprintf(m_str_lapTime[SECOND], "%02d:%02d:%03d ", m_minute[SECOND], m_second[SECOND], m_milliSecond[SECOND]);
	sprintf(m_str_lapTime[THIRD], "%02d:%02d:%03d ", m_minute[THIRD], m_second[THIRD], m_milliSecond[THIRD]);

	//ミリ秒
	//m_milliSecond[m_lapCount - 1] = getMilliSecond(m_flame);

	//秒
	//m_second[m_lapCount - 1] = getSecond(m_flame);

	//分
	//m_minute[m_lapCount - 1] = getMinute(m_second[m_lapCount - 1]);

	//second = second % 60;

	//スピード・ポジションの更新
	m_speed += m_accel;
	m_position += m_speed;

	//減速させる慣性
	m_speed *= 0.965f;


	//既定のコース領域から出ていないかの判定
	checkCourseOut();

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

		/*m_milliSecond[m_lapCount - 1] = m_milliSecond[m_lapCount - 1];
		m_second[m_lapCount - 1] = m_second[m_lapCount - 1];
		m_minute[m_lapCount - 1] = m_minute[m_lapCount - 1];*/

		//ミリ秒
		m_milliSecond[m_lapCount - 1] = getMilliSecond(m_flame);

		//秒
		m_second[m_lapCount - 1] = getSecond(m_flame);

		//分
		m_minute[m_lapCount - 1] = getMinute(m_second[m_lapCount - 1]);

		m_second[m_lapCount - 1] = m_second[m_lapCount - 1] % 60;


		/*sprintf(m_str_lapTime[FIRST], "%02d:%02d:%03d ", m_minute[FIRST], m_second[FIRST], m_milliSecond[FIRST]);
		sprintf(m_str_lapTime[SECOND], "%02d:%02d:%03d ", m_minute[SECOND], m_second[SECOND], m_milliSecond[SECOND]);
		sprintf(m_str_lapTime[THIRD], "%02d:%02d:%03d ", m_minute[THIRD], m_second[THIRD], m_milliSecond[THIRD]);*/

		//フレームの初期化
		m_flame = 0;

		m_lapCount++;
		m_checkFlag = false;
	}

	//ゴールしたかの判定
	if (checkIsGoal()){
		m_isGoal = true;
	}

}


//-------------------------------------
//自機の描画

void Player::draw(){
	glPushMatrix();
	{

		//float diffuse[] = { 255 / 255.f, 255 / 255.f, 255 / 255.f, 1 };
		//glMaterialfv(
		//	GL_FRONT,   // GLenum face
		//	GL_DIFFUSE, // GLenum pname
		//	diffuse);   // const GLfloat *params

		glTranslatef(m_position.x, m_position.y, m_position.z);

		glRotatef(m_rotate.y * 180 / M_PI, 0, 1, 0);
		glRotatef(180, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);

		//glScalef(m_scale.x, m_scale.y, m_scale.z);
		glScalef(0.18, 0.18, 0.18);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		std::vector<float>::iterator itr_v = m_boby.m_vertex.begin();
		glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

		std::vector<float>::iterator itr_n = m_boby.m_normal.begin();
		glNormalPointer(GL_FLOAT, 0, &(*itr_n));

		std::vector<unsigned short>::iterator itr_i = m_boby.m_index.begin();


		/*車体描画*/
		glDrawElements(GL_TRIANGLES, m_boby.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

		//glColor3f(0, 1, 0);
		//glBegin(GL_TRIANGLES);
		//{
		//	glVertex3f(0, 0, -1.5);//頭
		//	glVertex3f(-0.5, 0, 1);
		//	glVertex3f(0.5, 0, 1);
		//}
		//glEnd();

	}
	glPopMatrix();


	glPushMatrix();
	{

		//float diffuse[] = { 0 / 255.f, 0 / 255.f, 0 / 255.f, 1 };
		//glMaterialfv(
		//	GL_FRONT,   // GLenum face
		//	GL_DIFFUSE, // GLenum pname
		//	diffuse);   // const GLfloat *params

		static float angle = 0.f;
		static float scal = 0.18f;

		angle -= 5.f;

		glTranslatef(m_position.x + sin(m_rotate.y)*1.1, m_position.y + 0.5, m_position.z + cos(m_rotate.y)*1.1);
		glRotatef(m_rotate.y * 180 / M_PI, 0, 1, 0);
		glRotatef(angle, 1, 0, 0);
		glScalef(scal, scal, scal);

		std::vector<float>::iterator itr_v = m_backWheel.m_vertex.begin();
		glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

		std::vector<float>::iterator itr_n = m_backWheel.m_normal.begin();
		glNormalPointer(GL_FLOAT, 0, &(*itr_n));

		std::vector<unsigned short>::iterator itr_i = m_backWheel.m_index.begin();


		/*後輪描画*/
		glDrawElements(GL_TRIANGLES, m_backWheel.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

		//float def[] = { 1, 1, 1, 1 };
		//glMaterialfv(
		//	GL_FRONT,   // GLenum face
		//	GL_DIFFUSE, // GLenum pname
		//	def);   // const GLfloat *params
	}
	glPopMatrix();
}

//-------------------------------------
//自機の制御

void Player::control(unsigned int _pressedKey, unsigned int _downKeys, float _x, float _y, float _z){

	//前進(Aボタン)
	if (_pressedKey & BUTTON_A){

		//加速度の設定
		//-0.005fは補正値
		glm::vec3 accelIncrement(-0.015*sin(m_rotate.y), 0, -0.015*cos(m_rotate.y));
		m_accel = accelIncrement;
	}
	else{
		m_accel = { 0.f, 0.f, 0.f };
	}

	//正面右に移動
	if (_x > 0.9){
		m_rotate.y -= 0.02f;

	}

	//正面左に移動
	if (_x < -0.9){
		m_rotate.y += 0.02f;
	}

	//アイテムの使用
	if (_downKeys &  BUTTON_RB){



		//所持しているアイテムの個数を調べ
		//アイテム持っていなかったら(0)何もしない
		/*if (0 != hasMagicStoneNumber()){



		}
		else{}*/

	}

}


//-------------------------------------
//既定のコース領域から出ていないかの判断と
//出ていた場合の押し戻し処理

void Player::checkCourseOut(){

	if (m_position.x < 0.f){
		m_position.x = 0.f;
	}

	if (m_position.x > COURSE_WIDTH){
		m_position.x = COURSE_WIDTH;
	}

	if (m_position.z > 0){
		m_position.z = 0.f;
	}

	//256のままだと256番目のピクセル情報にアクセスしてしまうので補正値+1してある
	if (m_position.z < -COURSE_HEIGHT + 1){
		m_position.z = -COURSE_HEIGHT + 1;
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
//周回数が既定の周回数になった時点でtrueを返しゴールとする

bool Player::checkIsGoal(){

	if (LAP_MAX < m_lapCount){

		return true;

	}

	return false;

}

//-------------------------------------
//プレイヤーが持っているアイテムの個数を返す

int Player::hasMagicStoneNumber(){

	return m_hasMagicStone.size();

}