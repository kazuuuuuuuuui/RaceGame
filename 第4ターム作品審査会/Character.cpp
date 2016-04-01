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
#include"Fire.h"
#include"Blizzard.h"
#include"StrokeString.h"
#include"SoundManager.h"
#include"RaceManager.h"
#include"ImageManager.h"
#include"JoysticManager.h"
#include"CharacterManager.h"
#include"TimeManager.h"
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtx\transform.hpp"
#include"glut.h"

//-------------------------------------
//自機の更新
//ゴールした時点で更新を止める

void Character::Update(){

	//if (false == m_isGoal)
	//{
		//フレームの管理
		m_flame++;

		m_lapTimeCounter++;

		//ミリ秒
		m_milliSecond = oka::TimeManager::GetInstance()->GetMilliSecond(m_flame);
		m_lapMilliSecond[m_lapCount] = oka::TimeManager::GetInstance()->GetMilliSecond(m_lapTimeCounter);

		//秒
		m_second = oka::TimeManager::GetInstance()->GetSecond(m_flame);
		m_lapSecond[m_lapCount] = oka::TimeManager::GetInstance()->GetSecond(m_lapTimeCounter);

		//分
		m_minute = oka::TimeManager::GetInstance()->GetMinutes(m_second);
		m_lapMinute[m_lapCount] = oka::TimeManager::GetInstance()->GetMinutes(m_lapSecond[m_lapCount]);

		m_second = m_second % 60;
		m_lapSecond[m_lapCount] = m_lapSecond[m_lapCount] % 60;

		sprintf_s(m_totalTime, "%02d:%02d:%03d", m_minute, m_second, m_milliSecond);


		sprintf_s(m_lap, "%d", (m_lapCount + 1));

		//ダッシュゲージの回復
		m_dashPower += 0.1f;

		if (m_dashPower >= DASH_GAUGE_MAX)
		{
			m_dashPower = DASH_GAUGE_MAX;

			if (false == m_isCharged)
			{
				m_isCharged = true;
				oka::SoundManager::GetInstance()->Play("chargeComplete");
			}

		}


		//1周したかの判定
		if (countLap()){

			//フレームの初期化
			m_lapTimeCounter = 0;

			//チェックポイントの初期化
			for (int i = 0; i < Course::checkPointNum; i++)
			{
				m_passCheckPoint[i] = false;
			}

			//AIポイントの初期化
			for (int i = 0; i < Course::aimPointNum; i++)
			{
				m_passAIPoint[i] = false;
			}

			m_nowPoint = 0;

			sprintf_s(m_lapTime[FIRST], "%02d:%02d:%03d ", m_lapMinute[FIRST], m_lapSecond[FIRST], m_lapMilliSecond[FIRST]);
			sprintf_s(m_lapTime[SECOND], "%02d:%02d:%03d ", m_lapMinute[SECOND], m_lapSecond[SECOND], m_lapMilliSecond[SECOND]);
			sprintf_s(m_lapTime[THIRD], "%02d:%02d:%03d ", m_lapMinute[THIRD], m_lapSecond[THIRD], m_lapMilliSecond[THIRD]);

			m_lapCount++;

			if (m_contoroller.m_isConnect)
			{
				//1周目または2周目の時のみ鳴らす
				if (1 == m_lapCount)
				{
					oka::SoundManager::GetInstance()->Play("lapCountSE");
				}
				else if (2 == m_lapCount)
				{
					oka::SoundManager::GetInstance()->Play("finalLapSE");
			
				}
			}

		}

	//}

	//行列計算
	oka::Mat4x4 translate = oka::Mat4x4::Translate(oka::Vec3(m_transform.GetPosition().m_x, m_transform.GetPosition().m_y, m_transform.GetPosition().m_z));
	oka::Mat4x4 rotate = oka::Mat4x4::RotateY(m_transform.GetRotation().m_y + m_crashRotate)*oka::Mat4x4::RotateZ(m_transform.GetRotation().m_z);
	oka::Mat4x4 scale = oka::Mat4x4::Scale(m_transform.GetScale());

	//親の行列
	m_matrix = translate *rotate *scale;

	//車体
	m_body.m_matrix = m_matrix;

	//前輪
	m_frontWheel.m_transform.SetPositionX(0.0f);
	m_frontWheel.m_transform.SetPositionY(2.8f);
	m_frontWheel.m_transform.SetPositionZ(-9.0f);
	m_frontWheel.m_transform.SetRotation(m_transform.GetRotation());

	m_frontWheel.m_matrix = m_matrix;

	//後輪
	m_backWheel.m_transform.SetPositionX(0.0f);
	m_backWheel.m_transform.SetPositionY(3.1f);
	m_backWheel.m_transform.SetPositionZ(6.3f);
	m_backWheel.m_transform.SetRotation(m_transform.GetRotation());

	m_backWheel.m_matrix = m_matrix;

	//前輪座標
	//m_frontPosition.m_x = m_transform.GetPosition().m_x - sin(m_transform.GetRotation().m_y)*1.1f;
	//m_frontPosition.m_y = 0.5f;
	//m_frontPosition.m_z = m_transform.GetPosition().m_z - cos(m_transform.GetRotation().m_y)*1.1f;

	////後輪座標
	//m_backPosition.m_x = m_transform.GetPosition().m_x + sin(m_transform.GetRotation().m_y)*0.7f;
	//m_backPosition.m_y = 0.5f;
	//m_backPosition.m_z = m_transform.GetPosition().m_z + cos(m_transform.GetRotation().m_y)*0.7f;

	//スピード・ポジションの更新
	m_speed += (m_dashSpeed + m_accel);

	m_transform.SetPosition(m_transform.GetPosition() + m_speed);


	//煙の更新
	m_smoke.Update();
	m_smoke.m_basePosition.m_x = m_transform.GetPosition().m_x + sin(m_transform.GetRotation().m_y)*1.7f;
	m_smoke.m_basePosition.m_y = 0.5f;
	m_smoke.m_basePosition.m_z = m_transform.GetPosition().m_z + cos(m_transform.GetRotation().m_y)*1.7f;

	//減速させる慣性
	m_speed *= 0.965f;

	//ダッシュの減速処理
	m_dashSpeed *= 0.96;

	if (m_dashSpeed.length() <= 0.0001)
	{
		//ダッシュ状態解除
		m_isDash = false;
	}
	

	//車輪の回転スピード更新
	//*100は補正値
	m_wheelSpeed = m_speed.length() * 100.f;


	//スリップ処理
	slip();

	//チェックポイントを通過しているかの判定処理
	for (int i = 0; i < Course::checkPointNum; i++)
	{
		if (0 == i)
		{
			if (false == m_passCheckPoint[i] && RaceManager::GetInstance()->m_course->m_checkPoint[i].CheckPass(m_transform.GetPosition())){

				m_passCheckPoint[i] = true;
				m_nowPoint++;

			}

		}

		else
		{

			if (true == m_passCheckPoint[i - 1])
			{

				if (false == m_passCheckPoint[i] && RaceManager::GetInstance()->m_course->m_checkPoint[i].CheckPass(m_transform.GetPosition()))
				{
					m_passCheckPoint[i] = true;
					m_nowPoint++;
				}
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
	if (false == m_isGoal && checkIsGoal())
	{
		m_isGoal = true;
		m_lastRanking = m_ranking;

		oka::SoundManager::GetInstance()->Play("goalSE");
	}

}

//-------------------------------------
//自機の描画

void Character::Draw()
{
	//車体
	m_body.Draw();

	//前輪
	//m_frontWheel.Draw();

	//後輪
	//m_backWheel.Draw();

	//車体影
	//m_body.DrawShadow();

	////影部描画
	////後輪
	//glPushMatrix();
	//{
	//	//子供の行列
	//	glm::mat4 child = glm::scale(glm::vec3(0.92f, 0, 0.92f));
	//	//オフセット
	//	glm::mat4 offSet = glm::translate(glm::vec3(0.0f, 0.01f, 6.3f));
	//	glm::mat4 myMatrix = m_matrix * offSet *child;
	//	glMultMatrixf((GLfloat*)&myMatrix);
	//	std::vector<float>::iterator itr_v = m_backWheel.m_vertex.begin();
	//	glVertexPointer(3, GL_FLOAT, 0, &(*itr_v));
	//	std::vector<unsigned short>::iterator itr_i = m_backWheel.m_index.begin();
	//	/*後輪描画*/
	//	glDrawElements(GL_TRIANGLES, m_backWheel.m_indeces * 3, GL_UNSIGNED_SHORT, &(*itr_i));
	//}
	//glPopMatrix();

}



//-------------------------------------
//所持しているアイテムの描画

void Character::drawHasItem()
{
	for (unsigned int i = 0; i < m_hasItem.size(); i++)
	{

		//テクスチャの設定
		switch (m_hasItem[i]){
		case FIRE:

			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("ItemFire"));

			break;

		case BLIZZARD:

			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("ItemBlizzard"));

			break;

		}


		glPushMatrix();
		{
			glTranslatef(m_transform.GetPosition().m_x + sin(m_transform.GetRotation().m_y) * 2.8 + sin(m_transform.GetRotation().m_y)*i,
				0.5f,
				m_transform.GetPosition().m_z + cos(m_transform.GetRotation().m_y) * 2.8 + cos(m_transform.GetRotation().m_y)*i);

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
//自機の制御

void Character::control(unsigned short _pressedKey, unsigned int _downKeys, float _sThumbLX, float _sThumbLY)
{
	//エンジン音のピッチ調整

	oka::SoundManager::GetInstance()->ChangeVolume("Engine", pow(2, (m_speed.length()*15.f) / 12));

	if (false == m_isHitItem)
	{

		//前進(Aボタン)
		if (_pressedKey & XINPUT_GAMEPAD_A)
		{
			//加速度の設定
			//-0.005fは補正値
			oka::Vec3 accelIncrement(-0.015*sin(m_transform.GetRotation().m_y), 0.f, -0.015*cos(m_transform.GetRotation().m_y));
			m_accel = accelIncrement;
	
		}
		else
		{
			m_accel = { 0.f, 0.f, 0.f };
		}

		//正面右に移動
		if (_sThumbLX > 0.3)
		{
			m_transform.SetRotationY(m_transform.GetRotation().m_y-0.02f);

			_sThumbLX = 1.f;
			m_transform.SetRotationZ(m_transform.GetRotation().m_z + ((-1)*(_sThumbLX / 2) - m_transform.GetRotation().m_z)*0.1f);
		}

		//正面左に移動
		else if (_sThumbLX < -0.3)
		{
	
			m_transform.SetRotationY(m_transform.GetRotation().m_y + 0.02f);

			_sThumbLX = -1.f;
			m_transform.SetRotationZ(m_transform.GetRotation().m_z + ((-1)*(_sThumbLX / 2) - m_transform.GetRotation().m_z)*0.1f);
		}
		else
		{
			m_transform.SetRotationZ(m_transform.GetRotation().m_z + ((_sThumbLX / 2) - m_transform.GetRotation().m_z)*0.1f);
		}

		//アイテムの使用
		if (_downKeys &  XINPUT_GAMEPAD_LEFT_SHOULDER)
		{

			if (false == m_isDash)
			{

				if (hasItemNumber() > 0)
				{

					//使ったアイテムの種類によって
					//応じたエフェクトを出す

					//ファイアを使用した
					if (FIRE == hasItemLast())
					{
						Fire *fire = new Fire();
						fire->m_isActive = true;
						fire->m_basePosition = { m_transform.GetPosition().m_x - sin(m_transform.GetRotation().m_y) * 1.f, 0.5f,m_transform.GetPosition().m_z - cos(m_transform.GetRotation().m_y) * 1.f };
						fire->m_speed = { -sin(m_transform.GetRotation().m_y)*1.f, 0.f, -cos(m_transform.GetRotation().m_y)*1.f };
						oka::GameManager::GetInstance()->AddGameObject(fire);
						oka::SoundManager::GetInstance()->Play("fireSE");

					}

					//ブリザドを使用した
					else if (BLIZZARD == hasItemLast())
					{

						Blizzard *blizzard = new Blizzard();
						blizzard->m_isActive = true;
						blizzard->m_basePosition = { m_transform.GetPosition().m_x + sin(m_transform.GetRotation().m_y)*2.5f, 0.01f, m_transform.GetPosition().m_z + cos(m_transform.GetRotation().m_y)*2.5f };
						oka::GameManager::GetInstance()->AddGameObject(blizzard);
					}

					m_hasItem.pop_back();

				}

			}

		}

		//ダッシュ
		if (_downKeys &  XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{
			if (true == m_isCharged)
			{

				m_isCharged = false;
				m_isDash = true;

				m_dashPower = 0.0f;

				m_dashSpeed = oka::Vec3(-0.09f*sin(m_transform.GetRotation().m_y), 0.f, -0.09f*cos(m_transform.GetRotation().m_y));

			}
		}

	}

}




//-------------------------------------
//敵のAI

void Character::control()
{

	//向き調整
	//コースのAIポイントのx - 敵のx
	//コースのAIのz - 敵のz

	glm::vec2 v = { RaceManager::GetInstance()->m_course->m_aimPoint[m_nextPoint].m_position.m_x - m_transform.GetPosition().m_x,
		RaceManager::GetInstance()->m_course->m_aimPoint[m_nextPoint].m_position.m_z - m_transform.GetPosition().m_z };

	v = glm::normalize(v);

	//0.～0.018目安
	float sp = (((float)rand() / RAND_MAX) / 1000) * 28;

	m_accel.m_x = v.x*sp;
	m_accel.m_z = v.y*sp;

	//敵のAIの挙動制御

	if (RaceManager::GetInstance()->m_course->m_aimPoint[m_nextPoint].CheckPass(m_transform.GetPosition())){

		m_passAIPoint[m_nextPoint] = true;

		m_nextPoint++;

		if (Course::aimPointNum == m_nextPoint){
			m_nextPoint = 0;
		}

		m_pos_to_AIpoint = { RaceManager::GetInstance()->m_course->m_aimPoint[m_nextPoint].m_position.m_x - m_transform.GetPosition().m_x,
			RaceManager::GetInstance()->m_course->m_aimPoint[m_nextPoint].m_position.m_z - m_transform.GetPosition().m_z };
		m_pos_to_AIpoint = glm::normalize(m_pos_to_AIpoint);

		//角度からの向きベクトル
		OrientationVector = { -sin(m_transform.GetRotation().m_y), -cos(m_transform.GetRotation().m_y) };

		CompletionValue = 0.f;

	}

	//向きベクトルと向けたい方向のベクトルとの差分
	glm::vec2 dif = m_pos_to_AIpoint - OrientationVector;

	dif = dif  * CompletionValue;

	//自身の向きベクトルに差分を足したベクトル
	glm::vec2 OrientationVectorPulsDif = OrientationVector + dif;

	m_transform.SetRotationY(atan2f(-OrientationVectorPulsDif.x, -OrientationVectorPulsDif.y));

	//インクリメントする値によって
	//補完の滑らかさが変わる
	CompletionValue += 0.05f;

	if (CompletionValue >= 1){
		CompletionValue = 1.f;
	}


	//アイテムを使用するかの処理
	useItem();

}

//-------------------------------------
//アイテムを持ってた際にアイテムを使用する
//20秒に1回使用のチェックを行う

void Character::useItem(){

	if (0 == m_flame % 60 * 20)
	{
		if (hasItemNumber() > 0)
		{
			//ファイアを使用した
			if (FIRE == hasItemLast())
			{
				Fire *fire = new Fire();
				fire->m_isActive = true;
				fire->m_basePosition = { m_transform.GetPosition().m_x - sin(m_transform.GetRotation().m_y) * 1.f, 0.5f, m_transform.GetPosition().m_z - cos(m_transform.GetRotation().m_y) * 1.f };
				fire->m_speed = { -sin(m_transform.GetRotation().m_y)*1.f, 0.f, -cos(m_transform.GetRotation().m_y)*1.f };
				oka::GameManager::GetInstance()->AddGameObject(fire);
			}

			//ブリザドを使用した
			else if (BLIZZARD == hasItemLast())
			{

				Blizzard *blizzard = new Blizzard();
				blizzard->m_isActive = true;
				blizzard->m_basePosition = { m_transform.GetPosition().m_x + sin(m_transform.GetRotation().m_y)*2.5f, 0.01f, m_transform.GetPosition().m_z + cos(m_transform.GetRotation().m_y)*2.5f };
				oka::GameManager::GetInstance()->AddGameObject(blizzard);

			}

			m_hasItem.pop_back();



		}
	}
}

//-------------------------------------
//既定のコース領域から出ていないかの判断と
//出ていた場合の押し戻し処理

void Character::checkCourseOut()
{

	if (m_transform.GetPosition().m_x < 0.0f)
	{
		m_transform.SetPositionX(0.0f);
	}

	if (m_transform.GetPosition().m_x > COURSE_WIDTH)
	{
		m_transform.SetPositionX(COURSE_WIDTH);
	}

	if (m_transform.GetPosition().m_z > 0.0f)
	{
		m_transform.SetPositionZ(0.0f);
	}

	//256のままだと256番目のピクセル情報にアクセスしてしまうので補正値+1してある
	if (m_transform.GetPosition().m_z < 1-COURSE_HEIGHT)
	{
		m_transform.SetPositionZ(1 - COURSE_HEIGHT);
	}

}


//-------------------------------------
//目指しているチェックポイントまでの距離を返す

float Character::checkNextCheckPointLength()
{
	oka::Vec3 v;

	v = m_transform.GetPosition() - RaceManager::GetInstance()->m_course->m_checkPoint[m_nowPoint].m_position;

	return v.length();
}

//-------------------------------------
//プレイヤーがダートに入っているか判定
//入っていたらtrue 入っていなかったらfalseを返す

bool Character::inDart()
{

	//プレイヤーがどのピクセル上にいるか判断し
	//直下のピクセル情報によって判定する

	if (RaceManager::GetInstance()->m_course->m_buffer[COURSE_HEIGHT - 1 + (int)m_transform.GetPosition().m_z][(int)m_transform.GetPosition().m_x] == DART){

		return true;

	}
	else{

		return false;

	}
}

//-------------------------------------
//アイテムに当たった時のスリップ処理

void Character::slip()
{

	if (m_isHitItem)
	{
		m_speed = { 0.0f, 0.0f, 0.0f };
		
	}

	m_crashRotate *= 0.9f;

	if (m_crashRotate < 0.5f)
	{
		m_isHitItem = false;

	}


}

//-------------------------------------
//順位の描画

void Character::printRanking()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		{

			if (false == m_isGoal)
			{
				//順位に応じて貼るテクスチャを変える
				switch (m_ranking)
				{
				case 1:
					glColor4f(255 / 255.f, 201 / 255.f, 14 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank1st"));
					break;

				case 2:
					glColor4f(255 / 255.f, 255 / 255.f, 255 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank2nd"));
					break;

				case 3:
					glColor4f(188 / 255.f, 126 / 255.f, 92 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank3rd"));
					break;

				case 4:
					glColor4f(0 / 255.f, 255 / 255.f, 0 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank4th"));
					break;

				}

				glTranslatef(0.f, 0.f, 0);

			}

			else
			{
				//順位に応じて貼るテクスチャを変える
				switch (m_lastRanking) {
				case 1:
					glColor4f(255 / 255.f, 201 / 255.f, 14 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank1st"));
					break;

				case 2:
					glColor4f(255 / 255.f, 255 / 255.f, 255 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank2nd"));
					break;

				case 3:
					glColor4f(188 / 255.f, 126 / 255.f, 92 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank3rd"));
					break;

				case 4:
					glColor4f(0 / 255.f, 255 / 255.f, 0 / 255.f, 1);
					glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Rank4th"));
					break;

				}

				glTranslatef(50.f, 193.f, 0);

			}


			glBegin(GL_QUADS);
			{
				glTexCoord2f(0, 1);
				glVertex2f(0, 0);

				glTexCoord2f(1, 1);
				glVertex2f(80, 0);

				glTexCoord2f(1, 0);
				glVertex2f(80, 80);

				glTexCoord2f(0, 0);
				glVertex2f(0, 80);
			}
			glEnd();
		}
		glPopMatrix();

	}
	glPopAttrib();

}

//-------------------------------------
//GOALの描画

void printGoal()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	{

		glTranslatef(140, 185, 0);

		glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("Goal"));

		glBegin(GL_QUADS);
		{
			glColor4f(1, 0, 0, 1);
			glTexCoord2f(0, 1); glVertex2f(0, 0);
			glTexCoord2f(1, 1); glVertex2f(150, 0);
			glTexCoord2f(1, 0); glVertex2f(150, 80);
			glTexCoord2f(0, 0); glVertex2f(0, 80);
		}
		glEnd();
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

//-------------------------------------

//-------------------------------------
//ダッシュゲージのインターフェイス

void Character::printDashGauge(){

	//インターフェイス部分

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//アイコン部分
		glPushMatrix();
		{
			glTranslatef(5, 255, 0);

			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("DashIcon"));

			glBegin(GL_QUADS);
			{
				glColor4f(1, 1, 1, 1);
				glTexCoord2f(0, 1); glVertex2f(0, 0);
				glTexCoord2f(1, 1); glVertex2f(40, 0);
				glTexCoord2f(1, 0); glVertex2f(40, 40);
				glTexCoord2f(0, 0); glVertex2f(0, 40);
			}
			glEnd();
		}
		glPopMatrix();

		//ゲージ外枠
		glPushMatrix();
		{
			glTranslatef(42, 266, 0);

			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("DashGauge"));

			glBegin(GL_QUADS);
			{
				glColor4f(1, 1, 1, 1);
				glTexCoord2f(0, 0); glVertex2f(0, 0);
				glTexCoord2f(1, 0); glVertex2f(100, 0);
				glTexCoord2f(1, 1); glVertex2f(100, 15);
				glTexCoord2f(0, 1); glVertex2f(0, 15);
			}
			glEnd();
		}
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		//ゲージ部分

		glPushMatrix();
		{
			glTranslatef(46.5, 270.f, 0);

			glBegin(GL_QUADS);
			{
				if (DASH_GAUGE_MAX == m_dashPower) {
					glColor3f(1, rand() % 256 / 255.f, rand() % 256 / 255.f);
				}
				else {
					glColor3f(1, 0, 0);
				}
				glVertex2f(0, 0);
				glVertex2f(m_dashPower, 0);
				glVertex2f(m_dashPower, 7.f);
				glVertex2f(0, 7.f);
			}
			glEnd();

		}
		glPopMatrix();

	}
	glPopAttrib();

}

//-------------------------------------

//プレイヤーステータスの表示

void Character::printStatus()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_DEPTH_TEST);

		if (false == m_isGoal)
		{

			//ダッシュゲージの描画
			printDashGauge();

			float scale = 0.1f;
			oka::Vec3 color = oka::Vec3(1.0f, 0.0f, 0.0f);
			float width = 2.0f;

			oka::DrawString("LAP", glm::vec2(230.0f, 250.0f), scale, color, width);
			oka::DrawString("/", glm::vec2(275.0f, 250.0f), scale, color, width);
			oka::DrawString(RaceManager::GetInstance()->m_rapMax, glm::vec2(285.0f, 250.0f), scale, color, width);

			scale = 0.13f;
			oka::DrawString("TIME", glm::vec2(180.0f, 280.0f), scale, color, width);
			oka::DrawString(m_totalTime, glm::vec2(220.0f, 280.0f), scale, color, width);

			scale = 0.18f;
			oka::DrawString(m_lap, glm::vec2(260.0f, 250.0f), scale, color, width);

			scale = 0.08;
			oka::DrawString("LAP1", glm::vec2(220.0f, 230.0f), scale, color, width);
			oka::DrawString(m_lapTime[FIRST], glm::vec2(250.0f, 230.0f), scale, color, width);

			oka::DrawString("LAP2", glm::vec2(220.0f, 215.0f), scale, color, width);
			oka::DrawString(m_lapTime[SECOND], glm::vec2(250.0f, 215.0f), scale, color, width);

			oka::DrawString("LAP3", glm::vec2(220.0f, 200.0f), scale, color, width);
			oka::DrawString(m_lapTime[THIRD], glm::vec2(250.0f, 200.0f), scale, color, width);



		}
		else
		{
			printGoal();

			/*glColor3f(1, 0, 0);
			oka::DrawString("LAP1", 60.0f, 160.0f, 0.2f);
			oka::DrawString(m_lapTime[FIRST], 130.0f, 155.0f, 0.2f);

			oka::DrawString("LAP2", 60.0f, 115.0f, 0.2f);
			oka::DrawString(m_lapTime[SECOND], 130.0f, 115.0f, 0.2f);

			oka::DrawString("LAP3", 60.0f, 75.0f, 0.2f);
			oka::DrawString(m_lapTime[THIRD], 130.0f, 75.0f, 0.2f);

			oka::DrawString("TOTALTIME", 25.0f, 30.0f, 0.15f);
			oka::DrawString(m_totalTime, 130.0f, 30.0f, 0.2f);*/



			if (RaceManager::GetInstance()->IsRaceEnd())
			{
				//if ((oka::GameManager::GetInstance()->m_flame % 60) < 30)
				//{
				//	//oka::DrawString("PushStartButton!!", 220.0f, 10.0f, 0.08f);			
				//}
			}

		}
	}
}


//---------------------------------------------------------------
//プレイヤーがコースを順走して1周したかどうかの判定を行う
//ゴールの位置にいるときにチェックポイントを通過しているか判別する
//フラグがtrueの状態のときのみtrueを返し1周とカウントする

bool Character::countLap()
{

	if (RaceManager::GetInstance()->m_course->m_buffer[COURSE_HEIGHT - 1 + (int)m_transform.GetPosition().m_z][(int)m_transform.GetPosition().m_x] == GOAL)
	{
		bool fg = true;

		for (int i = 0; i < Course::checkPointNum; i++)
		{
			fg &= m_passCheckPoint[i];

		}

		if (fg)
		{
			return true;

		}
	}

	return false;

}

//-------------------------------------
//プレイヤーがゴールしたかの判定
//周回数が既定の周回数になった時点でtrueを返しゴールとする

bool Character::checkIsGoal()
{
	if (3 == m_lapCount)
	{
		return true;
	}

	return false;
}

//-------------------------------------
//プレイヤーが持っているアイテムの個数を返す

int Character::hasItemNumber()
{
	return m_hasItem.size();
}

//-------------------------------------
//プレイヤーがアイテムを持っているときのみ
//持っているアイテムのラストの種類を返す

int Character::hasItemLast()
{

	int itemLast = m_hasItem.size() - 1;

	return m_hasItem[itemLast];

}