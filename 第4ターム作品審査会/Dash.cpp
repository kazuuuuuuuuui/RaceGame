#include"Dash.h"

unsigned int dash_handle = 0;

void Dash::update()
{
	//パーティクルの更新
	for (int i = 0; i < DASH_PARTICLE_NUMBER; i++)
	{

		m_particle[i].m_alpha -= 0.05f;

		m_particle[i].m_transform.SetScale(m_particle[i].m_transform.GetScale()+0.1f);

		if (m_particle[i].m_alpha <= 0.f){
			m_particle[i].m_alpha = (float)rand() / RAND_MAX;
			m_particle[i].m_transform.SetScale(oka::Vec3(0.0f, 0.0f, 0.0f));
		}
	}
}

void Dash::draw(){

	//左右対称で2つ描画している
	glPushMatrix();
	{

		glTranslatef(m_basePosition.m_x, m_basePosition.m_y, m_basePosition.m_z);

		for (int i = 0; i < DASH_PARTICLE_NUMBER; i++){
			m_particle[i].draw(1, { 1.f, 1.f, 1.f }, dash_handle);
		}

		glRotatef(180, 0, 1, 0);

		for (int i = 0; i < DASH_PARTICLE_NUMBER; i++){
			m_particle[i].draw(1, { 1.f, 1.f, 1.f }, dash_handle);
		}

	}
	glPopMatrix();


}