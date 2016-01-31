#include"Character.h"
#include<stdio.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"GameManager.h"
#include"Course.h"
#include"Character.h"
#include"Item.h"
#include"camera.h"
#include"BmpImage.h"
#include"Material.h"
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtx\transform.hpp"
#include"glut.h"


//タイヤの位置等を後でいじる
//取り敢えず
extern int flame;
extern int milliSecond;
extern int second;
extern int minute;
extern bool startRace;

int getMilliSecond(int _flame);
int getSecond(int _flame);
int getMinute(int _second);

//-------------------------------------
//キャラクターすべてを管理するベクター
std::vector<Character*> character;

//-------------------------------------
//自機の更新
//ゴールした時点で更新を止める

void Character::update(){

	if (false == m_isGoal){

		//フレームの管理
		m_flame++;

		//ダッシュゲージの回復
		m_dashPower += 0.1f;

		if (m_dashPower >= DASH_GAUGE_MAX){

			m_dashPower = DASH_GAUGE_MAX;

		}


		//1周したかの判定
		if (countLap()){

			//ミリ秒
			m_milliSecond[m_lapCount - 1] = getMilliSecond(m_flame);

			//秒
			m_second[m_lapCount - 1] = getSecond(m_flame);

			//分
			m_minute[m_lapCount - 1] = getMinute(m_second[m_lapCount - 1]);

			m_second[m_lapCount - 1] = m_second[m_lapCount - 1] % 60;

			//フレームの初期化
			m_flame = 0;

			//チェックポイントの初期化
			for (int i = 0; i < CHECK_POINT_NUMBER; i++){
				m_passCheckPoint[i] = false;
			}

			//AIポイントの初期化
			for (int i = 0; i < AI_POINT_NUMBER; i++){
				m_passAIPoint[i] = false;
			}

			m_nowPoint = 0;

			m_lapCount++;


		}

	}

	sprintf_s(m_str_lapTime[FIRST], "%02d:%02d:%03d ", m_minute[FIRST], m_second[FIRST], m_milliSecond[FIRST]);
	sprintf_s(m_str_lapTime[SECOND], "%02d:%02d:%03d ", m_minute[SECOND], m_second[SECOND], m_milliSecond[SECOND]);
	sprintf_s(m_str_lapTime[THIRD], "%02d:%02d:%03d ", m_minute[THIRD], m_second[THIRD], m_milliSecond[THIRD]);

	//1フレーム前のポジション更新
	m_lastPosition = m_position;

	//スピード・ポジションの更新
	m_speed += (m_dashSpeed + m_accel);

	m_position += m_speed;

	//前輪と後輪のポジション更新

	//前輪座標
	m_frontPosition.x = m_position.x - sin(m_rotate.y)*1.55f;
	m_frontPosition.y = 0.5f;
	m_frontPosition.z = m_position.z - cos(m_rotate.y)*1.55f;

	//後輪座標
	m_backPosition.x = m_position.x + sin(m_rotate.y)*1.15f;
	m_backPosition.y = 0.5f;
	m_backPosition.z = m_position.z + cos(m_rotate.y)*1.15f;


	//煙の更新
	m_smoke.update();
	m_smoke.m_basePosition.x = m_position.x + sin(m_rotate.y)*1.7f;
	m_smoke.m_basePosition.y = 0.5f;
	m_smoke.m_basePosition.z = m_position.z + cos(m_rotate.y)*1.7f;

	//ダッシュエフェクトの更新
	if (nullptr != m_dash){
		m_dash->m_basePosition.x = m_position.x + sin(m_rotate.y)*0.8;
		m_dash->m_basePosition.y = -0.2f;
		m_dash->m_basePosition.z = m_position.z + cos(m_rotate.y)*0.8;
	}

	//減速させる慣性
	m_speed *= 0.965f;

	//ダッシュの減速処理
	m_dashSpeed *= 0.96;

	if (m_dash != NULL){

		if (glm::length(m_dashSpeed) <= 0.0001){
			//ダッシュ状態解除
			m_isDash = false;
			m_dash->m_isActive = false;
		}

	}

	//printf("%f\n", glm::length(m_dashSpeed));


	//車輪の回転スピード更新
	//*100は補正値
	m_wheelSpeed = glm::length(m_speed) * 100;


	//スリップ処理
	slip();

	//チェックポイントを通過しているかの判定処理
	for (int i = 0; i < CHECK_POINT_NUMBER; i++){

		if (false == m_passCheckPoint[i] && course->m_checkPoint[i].checkPassFlag(m_position)){


			m_passCheckPoint[i] = true;
			m_nowPoint++;


		}

	}

	//敵のAIの挙動制御
	for (int i = 0; i < AI_POINT_NUMBER; i++){

		if (false == m_passAIPoint[i] && course->m_AIPoint[i].checkPassFlag(m_position)){

			m_passAIPoint[i] = true;

			m_nextPoint++;

			if (AI_POINT_NUMBER == m_nextPoint){
				m_nextPoint = 0;
			}

		}

	}

	//目指しているチェックポイントへの距離の更新
	m_nextCheckPointLength = checkNextCheckPointLength();

	//既定のコース領域から出ていないかの判定
	checkCourseOut();

	//ダートに入ったかの判定と処理
	if (inDart()){
		m_speed *= 0.9f;
	}

	//ゴールしたかの判定
	if (checkIsGoal()){
		m_isGoal = true;
	}

}

//-------------------------------------
//自機の描画

void Character::draw(){

	/*車体描画*/
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{

		glEnable(GL_LIGHTING);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glPushMatrix();
		{

			//行列計算
			glm::mat4 translate = glm::translate(glm::vec3(m_position.x, m_position.y, m_position.z));

			glm::mat4 rotate = glm::rotate(m_rotate.y + m_crashRotate, glm::vec3(0, 1, 0))*
				glm::rotate(m_rotate.z, glm::vec3(0, 0, 1));


			glm::mat4 scale = glm::scale(glm::vec3(m_scale.x, m_scale.y, m_scale.z));

			//親の行列
			m_matrix = translate *rotate *scale;

			//行列適応
			glMultMatrixf((GLfloat*)&m_matrix);

			std::vector<float>::iterator itr_v = m_body.m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

			std::vector<float>::iterator itr_n = m_body.m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*itr_n));

			std::vector<unsigned short>::iterator itr_i = m_body.m_index.begin();


			//マテリアルの設定

			/*	switch (m_type){

				case PLAYER1:

				float diffuse[4] = { 1, 0, 0, 1 };
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

				break;

				case PLAYER2:

				float diffuse[4] = { 0, 1, 0, 1 };
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

				break;

				case PLAYER3:

				float diffuse[4] = { 0, 0, 1, 1 };
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

				break;

				case PLAYER4:

				float diffuse[4] = { 0, 1, 1, 1 };
				glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

				break;
				}*/

			/*float specular[] = { 1, 0, 0, 1 };
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialf(GL_FRONT, GL_SHININESS, 100);*/

			glDrawElements(GL_TRIANGLES, m_body.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

		}
		glPopMatrix();


		//回転処理
		static float angle = 0;

		//後輪
		glPushMatrix();
		{
			angle -= m_wheelSpeed;
			angle *= 0.98f;

			//angleの値を-10000～0で扱うため
			if (angle < -200.f){
				angle = 0.f;
			}

			glm::mat4 childRotate = glm::rotate(angle, glm::vec3(1, 0, 0));

			glm::mat4 childScale = glm::scale(glm::vec3(0.9f, 0.9f, 0.9f));

			//子供の行列
			glm::mat4 child = childRotate * childScale;

			//オフセット
			glm::mat4 offSet = glm::translate(glm::vec3(0.0f, 3.1f, 6.3f));

			glm::mat4 myMatrix = m_matrix * offSet *child;


			glMultMatrixf((GLfloat*)&myMatrix);


			std::vector<float>::iterator itr_v = m_backWheel.m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

			std::vector<float>::iterator itr_n = m_backWheel.m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*itr_n));

			std::vector<unsigned short>::iterator itr_i = m_backWheel.m_index.begin();

			float diffuse[] = { 0, 0, 0, 1 };
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);

			/*後輪描画*/
			glDrawElements(GL_TRIANGLES, m_backWheel.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

		}
		glPopMatrix();


		//前輪
		glPushMatrix();
		{

			glm::mat4 childRotate = glm::rotate(angle, glm::vec3(1, 0, 0));

			glm::mat4 childScale = glm::scale(glm::vec3(0.72f, 0.72f, 0.72f));

			//子供の行列
			glm::mat4 child = childRotate * childScale;

			//オフセット
			glm::mat4 offSet = glm::translate(glm::vec3(0.0f, 2.8f, -9.f));

			glm::mat4 myMatrix = m_matrix * offSet *child;

			glMultMatrixf((GLfloat*)&myMatrix);

			std::vector<float>::iterator itr_v = m_backWheel.m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

			std::vector<float>::iterator itr_n = m_backWheel.m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*itr_n));

			std::vector<unsigned short>::iterator itr_i = m_backWheel.m_index.begin();

			glDrawElements(GL_TRIANGLES, m_backWheel.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

		}
		glPopMatrix();

	}
	glPopAttrib();

	//影部描画
	//車体

	glColor3f(100 / 255.f, 100 / 255.f, 100 / 255.f);

	glPushMatrix();
	{

		//行列計算
		glm::mat4 parentTranslate = glm::translate(glm::vec3(m_position.x, 0.01f, m_position.z));

		glm::mat4 parentRotate = glm::rotate(m_rotate.y + m_crashRotate, glm::vec3(0, 1, 0));

		glm::mat4 parentScale = glm::scale(glm::vec3(m_scale.x, 0, m_scale.z));

		//親の行列
		m_matrix = parentTranslate *parentRotate * parentScale;

		//行列適応
		glMultMatrixf((GLfloat*)&m_matrix);

		std::vector<float>::iterator itr_v = m_body.m_vertex.begin();
		glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

		std::vector<unsigned short>::iterator itr_i = m_body.m_index.begin();

		glDrawElements(GL_TRIANGLES, m_body.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

	}
	glPopMatrix();


	//影部描画
	//後輪

	glPushMatrix();
	{

		//子供の行列
		glm::mat4 child = glm::scale(glm::vec3(0.92f, 0, 0.92f));

		//オフセット
		glm::mat4 offSet = glm::translate(glm::vec3(0.0f, 0.01f, 6.3f));

		glm::mat4 myMatrix = m_matrix * offSet *child;


		glMultMatrixf((GLfloat*)&myMatrix);




		std::vector<float>::iterator itr_v = m_backWheel.m_vertex.begin();
		glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));

		std::vector<unsigned short>::iterator itr_i = m_backWheel.m_index.begin();


		/*後輪描画*/
		glDrawElements(GL_TRIANGLES, m_backWheel.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));

	}
	glPopMatrix();

	//debug
	//本体
	glColor3f(1, 1, 1);
	glPushMatrix();
	{
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(m_rotate.y * 180 / M_PI, 0, 1, 0);
		glScalef(m_scale.x, m_scale.y, m_scale.z);
		glutSolidCube(1);
	}
	glPopMatrix();
	//前
	glPushMatrix();
	{
		glTranslatef(m_frontPosition.x, m_frontPosition.y - 0.5f, m_frontPosition.z);
		glRotatef(m_rotate.y * 180 / M_PI, 0, 1, 0);
		glScalef(m_scale.x, m_scale.y, m_scale.z);
		glutSolidCube(1);
	}
	glPopMatrix();
	//後ろ
	glPushMatrix();
	{
		glTranslatef(m_backPosition.x, m_backPosition.y - 0.5f, m_backPosition.z);
		glRotatef(m_rotate.y * 180 / M_PI, 0, 1, 0);
		glScalef(m_scale.x, m_scale.y, m_scale.z);
		glutSolidCube(1);
	}
	glPopMatrix();


}


//-------------------------------------
//所持しているアイテムの描画

void Character::drawHasItem(){

	for (unsigned int i = 0; i < m_hasItem.size(); i++){


		//テクスチャの設定
		switch (m_hasItem[i]){
		case FIRE:

			glBindTexture(GL_TEXTURE_2D, ItemFire);

			break;

		case BLIZZARD:

			glBindTexture(GL_TEXTURE_2D, ItemBlizzard);

			break;

		}


		glPushMatrix();
		{
			glTranslatef(m_position.x + sin(m_rotate.y) * 2.8 + sin(m_rotate.y)*i,
				0.5f,
				m_position.z + cos(m_rotate.y) * 2.8 + cos(m_rotate.y)*i);

			glColor3f(1, 1, 1);

			double s, t0, t1, r0, r1, th0, th1, phi;
			double p[2][3];

			for (int j = 0; j < ITEM_STACK; j++){
				t0 = (double)j / (double)ITEM_STACK;
				t1 = (double)(j + 1) / (double)ITEM_STACK;
				th0 = M_PI * t0;
				th1 = M_PI * t1;
				r0 = ITEM_RADIUS * sin(th0);
				r1 = ITEM_RADIUS * sin(th1);
				p[0][2] = ITEM_RADIUS * cos(th0);
				p[1][2] = ITEM_RADIUS * cos(th1);

				t0 = (1.0 - t0) * ITEM_REPEAT_T;
				t1 = (1.0 - t1) * ITEM_REPEAT_T;

				glEnable(GL_TEXTURE_2D);

				glBegin(GL_QUAD_STRIP);
				for (int i = 0; i <= ITEM_SLICE; i++){
					s = (double)i / (double)ITEM_SLICE;
					phi = 2.0 * M_PI * s;
					p[0][0] = -r0 * cos(phi);
					p[0][1] = -r0 * sin(phi);
					p[1][0] = -r1 * cos(phi);
					p[1][1] = -r1 * sin(phi);

					s *= ITEM_REPEAT_S;

					glTexCoord2d(s, t0);
					glNormal3dv(p[0]);
					glVertex3dv(p[0]);

					glTexCoord2d(s, t1);
					glNormal3dv(p[1]);
					glVertex3dv(p[1]);
				}
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

		}
		glPopMatrix();

	}

}


//-------------------------------------
//既定のコース領域から出ていないかの判断と
//出ていた場合の押し戻し処理

void Character::checkCourseOut(){

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
//目指しているチェックポイントまでの距離を返す

float Character::checkNextCheckPointLength(){

	glm::vec3 v;

	v = m_position - course->m_checkPoint[m_nowPoint].m_position;

	return glm::length(v);
}

//-------------------------------------
//プレイヤーがダートに入っているか判定
//入っていたらtrue 入っていなかったらfalseを返す

bool Character::inDart(){

	//プレイヤーがどのピクセル上にいるか判断し
	//直下のピクセル情報によって判定する

	if (course->m_buffer[COURSE_HEIGHT - 1 + (int)m_position.z][(int)m_position.x] == DART){

		return true;

	}
	else{

		return false;

	}
}

//-------------------------------------
//アイテムに当たった時のスリップ処理

void Character::slip(){

	if (m_isHitItem){

		m_speed = { 0.f, 0.f, 0.f };

	}

	m_crashRotate *= 0.9f;

	if (m_crashRotate < 0.5f){

		m_isHitItem = false;

	}


}



//-------------------------------------
//プレイヤーがコースを順走して1周したかどうかの判定を行う
//ゴールの位置にいるときにチェックポイントを通過しているか判別する
//フラグがtrueの状態のときのみtrueを返し1周とカウントする

bool Character::countLap(){

	if (course->m_buffer[COURSE_HEIGHT - 1 + (int)m_position.z][(int)m_position.x] == GOAL){

		bool fg = true;

		for (int i = 0; i < CHECK_POINT_NUMBER; i++){

			fg &= m_passCheckPoint[i];

		}

		if (fg == true){

			return true;

		}


	}

	return false;

}

//-------------------------------------
//プレイヤーがゴールしたかの判定
//周回数が既定の周回数になった時点でtrueを返しゴールとする

bool Character::checkIsGoal(){

	if (LAP_MAX < m_lapCount){

		return true;

	}

	return false;

}

//-------------------------------------
//プレイヤーが持っているアイテムの個数を返す

int Character::hasItemNumber(){

	return m_hasItem.size();

}

//-------------------------------------
//プレイヤーがアイテムを持っているときのみ
//持っているアイテムのラストの種類を返す

int Character::hasItemLast(){

	int itemLast = m_hasItem.size() - 1;

	return m_hasItem[itemLast];

}