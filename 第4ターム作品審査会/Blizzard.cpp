#include"SoundManager.h"
#include"CharacterManager.h"
#include"ImageManager.h"
#include"Blizzard.h"
#include"Character.h"
#include"glut.h"

void Blizzard::Update()
{
	//接触判定
	//当たったプレイヤーのisHitItemフラグをtrue
	//当たったアイテムのisActiveフラグをfalseにする

	for (unsigned int i = 0; i < CharacterManager::GetInstance()->GetCharacterNumber(); i++)
	{

		if (isHit(CharacterManager::GetInstance()->m_character[i]->m_transform.GetPosition()))
		{
			oka::SoundManager::GetInstance()->Play("slipSE");
			m_isActive = false;
			CharacterManager::GetInstance()->m_character[i]->m_isHitItem = true;
			CharacterManager::GetInstance()->m_character[i]->m_dashSpeed = { 0.f, 0.f, 0.f };
			CharacterManager::GetInstance()->m_character[i]->m_transform.SetRotationZ(0.0f);
			CharacterManager::GetInstance()->m_character[i]->m_crashRotate = 360000.f*(M_PI / 180);

		}
	}

}


void Blizzard::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{

		glDisable(GL_LIGHTING);

		glPushMatrix();
		{
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_DEPTH_TEST);
			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("EffectBlizzard"));

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);

			glTranslatef(m_basePosition.m_x, m_basePosition.m_y, m_basePosition.m_z);
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
		}
		glPopMatrix();
	}
	glPopAttrib();

}

//-------------------------------------
//全プレイヤーの座標を受け取って当たり判定を取る
//既定の範囲内まで近付いたらtrue そうでなければfalseを返す

bool Blizzard::isHit(oka::Vec3 _position)
{
	//プレイヤーと設置されたブリザードとのベクトル
	oka::Vec3 v;

	v.m_x = m_basePosition.m_x - _position.m_x;
	v.m_y = 0;
	v.m_z = m_basePosition.m_z - _position.m_z;

	float length = v.Length();

	//範囲は要修正
	if (length < 2.f){

		return true;

	}

	return false;

}
