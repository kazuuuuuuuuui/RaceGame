#include"Fire.h"
#include"Character.h"

#include"Enemy.h"


void Fire::update(){

	m_basePosition += m_speed;

	//接触判定
	//当たったプレイヤーのisHitItemフラグをtrue
	//当たったアイテムのisActiveフラグをfalseにする

	for (unsigned int i = 0; i < character.size(); i++){

		if (isHit(character[i]->transform.m_position)){

			slip_ES->play();
			m_isActive = false;
			character[i]->m_isHitItem = true;
			character[i]->transform.m_rotate.z = 0.f;
			character[i]->m_crashRotate = 360000.f*(M_PI / 180);

		}
	}

	for (int i = 0; i < FIRE_PARTICLE_NUMBER; i++){
		m_particle[i].m_alpha -= 0.025f;

		m_particle[i].transform.m_scale += 0.04f;
		m_particle[i].transform.m_position += m_particle[i].m_speed*m_particle[i].m_alpha;

		if (m_particle[i].m_alpha <= 0.f){
			m_particle[i].m_alpha = (float)rand() / RAND_MAX;
			m_particle[i].transform.m_scale = { 0.f, 0.f, 0.f };

			m_particle[i].m_speed.x = ((float)rand() / RAND_MAX - 0.5)*0.01f;//-0.05から0.05の値
			m_particle[i].m_speed.y = (((float)rand() / RAND_MAX - 0.5)*.5) *.04;
			m_particle[i].m_speed.z = ((float)rand() / RAND_MAX - 0.5)*0.01f;//-0.05から0.05の値;
		}
	}
}

void Fire::draw(){

	glPushMatrix();
	{

		glTranslatef(m_basePosition.x, m_basePosition.y, m_basePosition.z);

		for (int i = 0; i < FIRE_PARTICLE_NUMBER; i++){
			m_particle[i].draw(0, { 1.f, 0.25f, 0.125f }, smoke_handle);
		}

	}
	glPopMatrix();


	//影

	glPushMatrix();
	{

		glTranslatef(m_basePosition.x, 0.1, m_basePosition.z);
		glRotatef(90, 1, 0, 0);

		glColor3f(110.f / 255.f, 110.f / 255.f, 110.f / 255.f);

		Circle2DFill(0.3, 0, 0);
	}
	glPopMatrix();

}

//-------------------------------------
//全プレイヤーの座標を受け取って当たり判定を取る
//既定の範囲内まで近付いたらtrue そうでなければfalseを返す

bool Fire::isHit(glm::vec3 _position){

	//プレイヤーとファイアとのベクトル
	glm::vec3 v;

	v.x = m_basePosition.x - _position.x;
	v.y = 0;
	v.z = m_basePosition.z - _position.z;

	float length = glm::length(v);

	if (length < 1.5f){

		return true;

	}

	return false;

}