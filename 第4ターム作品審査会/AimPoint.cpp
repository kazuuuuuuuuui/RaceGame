#define _USE_MATH_DEFINES
#include<math.h>
#include"Vec3.h"
#include"AimPoint.h"
#include"CheckPoint.h"

bool AimPoint::CheckPass(oka::Vec3 _position)
{
	oka::Vec3 dis;

	dis.m_x = (m_position.m_x - _position.m_x);
	dis.m_y = (m_position.m_y - _position.m_y);
	dis.m_z = (m_position.m_z - _position.m_z);

	float length = sqrt(dis.m_x*dis.m_x+ dis.m_y*dis.m_y + dis.m_z*dis.m_z);

	float rad = 15.f;

	if (length < rad)
	{
		return true;
	}
	else
	{
		return false;
	}
}