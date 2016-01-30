#include"Smoke.h"
#include"Player.h"
#include"Character.h"

void Smoke::update(){

	for (int i = 0; i < SMOKE_PARTICLE_NUMBER; i++){
		m_particle[i].m_alpha -= 0.05f;

		m_particle[i].m_scale += 0.03f;
		m_particle[i].m_position += m_particle[i].m_speed*m_particle[i].m_alpha;

		if (m_particle[i].m_alpha <= 0.f){
			m_particle[i].m_alpha = (float)rand() / RAND_MAX;
			m_particle[i].m_scale = { 0.f, 0.f, 0.f };

			//m_particle[i].m_speed.x = ((float)rand() / RAND_MAX - 0.5)*0.01f;//-0.05‚©‚ç0.05‚Ì’l
			//m_particle[i].m_speed.y = (((float)rand() / RAND_MAX - 0.5)*.5) *.05;
			//m_particle[i].m_speed.z = ((float)rand() / RAND_MAX - 0.5)*0.01f;//-0.05‚©‚ç0.05‚Ì’l;
		}
	}
}

void Smoke::draw(){

	glPushMatrix();
	{
		glTranslatef(m_basePosition.x, m_basePosition.y, m_basePosition.z);

		for (int i = 0; i < SMOKE_PARTICLE_NUMBER; i++){
			m_particle[i].draw({ 128.f / 256.f, 128.f / 256.f, 128.f / 256.f, });
		}

	}
	glPopMatrix();

}