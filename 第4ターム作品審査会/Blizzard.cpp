#include"Blizzard.h"
#include"Character.h"
#include"Player.h"
#include"glut.h"

void Blizzard::update(){

	//接触判定
	//当たったプレイヤーのisHitItemフラグをtrue
	//当たったアイテムのisActiveフラグをfalseにする

	//for (unsigned int i = 0; i < character.size(); i++){

	//	if (isHit(character[i]->m_position)){
	if (isHit(player->m_position)){

		m_isActive = false;
		player->m_isHitItem = true;
		player->m_crashRotate = 360000.f*(M_PI / 180);

	}

	//		character[i]->m_isHitItem = true;

	//	}
	//}

}


void Blizzard::draw(){

	glPushMatrix();
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glBindTexture(GL_TEXTURE_2D, EffectBlizzard);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		glTranslatef(m_basePosition.x, m_basePosition.y, m_basePosition.z);
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
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);

	}
	glPopMatrix();


}

//-------------------------------------
//全プレイヤーの座標を受け取って当たり判定を取る
//既定の範囲内まで近付いたらtrue そうでなければfalseを返す

bool Blizzard::isHit(glm::vec3 _position){

	//プレイヤーと設置されたブリザードとのベクトル
	glm::vec3 v;

	v.x = m_basePosition.x - _position.x;
	v.y = 0;
	v.z = m_basePosition.z - _position.z;

	float length = glm::length(v);

	//範囲は要修正
	if (length < 2.f){

		return true;

	}

	return false;

}
