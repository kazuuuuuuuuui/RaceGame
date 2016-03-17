#include"Smoke.h"
#include"Fire.h"
#include"Character.h"

void Smoke::update()
{

	for (int i = 0; i < SMOKE_PARTICLE_NUMBER; i++)
	{
		m_particle[i].m_alpha -= 0.05f;

		m_particle[i].m_transform.SetScale(m_particle[i].m_transform.GetScale() + 0.03);
		m_particle[i].m_transform.GetPosition() += m_particle[i].m_speed*m_particle[i].m_alpha;

		if (m_particle[i].m_alpha <= 0.f){
			m_particle[i].m_alpha = (float)rand() / RAND_MAX;
			m_particle[i].m_transform.SetScale(oka::Vec3(0.0f, 0.0f, 0.0f));

		}
	}
}

void Smoke::draw()
{
	glPushMatrix();
	{
		glTranslatef(m_basePosition.m_x, m_basePosition.m_y, m_basePosition.m_z);

		for (int i = 0; i < SMOKE_PARTICLE_NUMBER; i++){
			m_particle[i].draw(0,{ 128.f / 256.f, 128.f / 256.f, 128.f / 256.f, }, smoke_handle);
		}

	}
	glPopMatrix();

}