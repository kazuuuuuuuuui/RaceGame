#include"SoundManager.h"
#include"Fire.h"
#include"Character.h"

void Fire::update(){

	m_basePosition += m_speed;

	//�ڐG����
	//���������v���C���[��isHitItem�t���O��true
	//���������A�C�e����isActive�t���O��false�ɂ���

	for (unsigned int i = 0; i < character.size(); i++){

		if (isHit(character[i]->m_transform.GetPosition())){

			SoundManager::getInstance()->m_sounds["slipSE"]->play();
			m_isActive = false;
			character[i]->m_isHitItem = true;
			character[i]->m_transform.SetRotationZ(0.0f);
			character[i]->m_crashRotate = 360000.f*(M_PI / 180);

		}
	}

	for (int i = 0; i < FIRE_PARTICLE_NUMBER; i++)
	{
		m_particle[i].m_alpha -= 0.025f;

		m_particle[i].m_transform.SetScale(m_particle[i].m_transform.GetScale()+0.04f);

		m_particle[i].m_transform.GetPosition() += m_particle[i].m_speed*m_particle[i].m_alpha;

		if (m_particle[i].m_alpha <= 0.f){
			m_particle[i].m_alpha = (float)rand() / RAND_MAX;
			m_particle[i].m_transform.SetScale(oka::Vec3(0.0f, 0.0f, 0.0f));

			m_particle[i].m_speed.m_x = ((float)rand() / RAND_MAX - 0.5)*0.01f;//-0.05����0.05�̒l
			m_particle[i].m_speed.m_y = (((float)rand() / RAND_MAX - 0.5)*.5) *.04;
			m_particle[i].m_speed.m_z = ((float)rand() / RAND_MAX - 0.5)*0.01f;//-0.05����0.05�̒l;
		}
	}
}

void Fire::draw(){

	glPushMatrix();
	{

		glTranslatef(m_basePosition.m_x, m_basePosition.m_y, m_basePosition.m_z);

		for (int i = 0; i < FIRE_PARTICLE_NUMBER; i++){
			m_particle[i].draw(0, { 1.f, 0.25f, 0.125f }, smoke_handle);
		}

	}
	glPopMatrix();


	//�e

	glPushMatrix();
	{

		glTranslatef(m_basePosition.m_x, 0.1, m_basePosition.m_z);
		glRotatef(90, 1, 0, 0);

		glColor3f(110.f / 255.f, 110.f / 255.f, 110.f / 255.f);

		Circle2DFill(0.3, 0, 0);
	}
	glPopMatrix();

}

//-------------------------------------
//�S�v���C���[�̍��W���󂯎���ē����蔻������
//����͈͓̔��܂ŋߕt������true �����łȂ����false��Ԃ�

bool Fire::isHit(oka::Vec3 _position){

	//�v���C���[�ƃt�@�C�A�Ƃ̃x�N�g��
	oka::Vec3 v;

	v.m_x = m_basePosition.m_x - _position.m_x;
	v.m_y = 0;
	v.m_z = m_basePosition.m_z - _position.m_z;

	float length = v.length();

	if (length < 1.5f){

		return true;

	}

	return false;

}