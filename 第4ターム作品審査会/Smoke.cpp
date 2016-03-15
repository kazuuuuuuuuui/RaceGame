#include"Smoke.h"
#include"Fire.h"
#include"Character.h"

void Smoke::update(){

	for (int i = 0; i < SMOKE_PARTICLE_NUMBER; i++){
		m_particle[i].m_alpha -= 0.05f;

		m_particle[i].transform.m_scale += 0.03f;
		m_particle[i].transform.m_position += m_particle[i].m_speed*m_particle[i].m_alpha;

		if (m_particle[i].m_alpha <= 0.f){
			m_particle[i].m_alpha = (float)rand() / RAND_MAX;
			m_particle[i].transform.m_scale = { 0.f, 0.f, 0.f };

		}
	}
}

void Smoke::draw(){

	glPushMatrix();
	{
		glTranslatef(m_basePosition.m_x, m_basePosition.m_y, m_basePosition.m_z);

		for (int i = 0; i < SMOKE_PARTICLE_NUMBER; i++){
			m_particle[i].draw(0,{ 128.f / 256.f, 128.f / 256.f, 128.f / 256.f, }, smoke_handle);
		}

	}
	glPopMatrix();

}