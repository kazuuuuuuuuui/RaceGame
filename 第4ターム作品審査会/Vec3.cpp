#include"Vec3.h"
#include<math.h>
#include<assert.h>

namespace oka {

	//-------------------------------------
	//�f�t�H���g�R���X�g���N�^

	Vec3::Vec3():
		m_x(0), m_y(0), m_z(0)
	{}

	//-------------------------------------
	//�����t���R���X�g���N�^
	//�����Ƃ��Ď󂯎�����l�Ń����o��������

	Vec3::Vec3(const float _x, const float _y, const float _z):
		m_x(_x), m_y(_y), m_z(_z)
	{}

	//-------------------------------------
	//���Z�q�̃I�[�o�[���[�h

	//vec3+vec3
	Vec3 Vec3::operator+(const Vec3 &_v)const
	{
		Vec3 out;
		out.m_x = this->m_x + _v.m_x;
		out.m_y = this->m_y + _v.m_y;
		out.m_z = this->m_z + _v.m_z;

		return out;
	}

	//vec3-vec3
	Vec3 Vec3::operator-(const Vec3 &_v)const
	{
		Vec3 out;
		out.m_x = this->m_x - _v.m_x;
		out.m_y = this->m_y - _v.m_y;
		out.m_z = this->m_z - _v.m_z;
		return out;
	}

	//vec3*vec3
	Vec3 Vec3::operator*(const Vec3 &_v)const
	{
		Vec3 out;
		out.m_x = this->m_x * _v.m_x;
		out.m_y = this->m_y * _v.m_y;
		out.m_z = this->m_z * _v.m_z;
		return out;
	}

	//vec3 / vec3
	Vec3 Vec3::operator/(const Vec3 &_v)const
	{
		Vec3 out;
		out.m_x = this->m_x / _v.m_x;
		out.m_y = this->m_y / _v.m_y;
		out.m_z = this->m_z / _v.m_z;
		return out;
	}

	//vec3+=vec3
	Vec3 &Vec3::operator +=(const Vec3 &_v)
	{
		this->m_x += _v.m_x;
		this->m_y += _v.m_y;
		this->m_z += _v.m_z;

		return *this;
	}

	//vec3-=vec3
	Vec3 &Vec3::operator -=(const Vec3 &_v)
	{
		this->m_x -= _v.m_x;
		this->m_y -= _v.m_y;
		this->m_z -= _v.m_z;

		return *this;
	}

	//vec3*=vec3
	Vec3 &Vec3::operator *=(const Vec3 &_v)
	{
		this->m_x *= _v.m_x;
		this->m_y *= _v.m_y;
		this->m_z *= _v.m_z;

		return *this;
	}

	//vec3/=vec3
	Vec3 &Vec3::operator /=(const Vec3 &_v)
	{
		this->m_x /= _v.m_x;
		this->m_y /= _v.m_y;
		this->m_z /= _v.m_z;

		return *this;
	}

	//vec3 = vec3 + float
	Vec3 Vec3::operator+(const float _s)const
	{
		Vec3 out;
		out.m_x = this->m_x + _s;
		out.m_y = this->m_y + _s;
		out.m_z = this->m_z + _s;

		return out;
	}

	//vec3 = vec3 - float
	Vec3 Vec3::operator-(const float _s)const
	{
		Vec3 out;
		out.m_x = this->m_x - _s;
		out.m_y = this->m_y - _s;
		out.m_z = this->m_z - _s;

		return out;
	}

	//vec3 = vec3 * float
	Vec3 Vec3::operator*(const float _s)const
	{
		Vec3 out;
		out.m_x = this->m_x * _s;
		out.m_y = this->m_y * _s;
		out.m_z = this->m_z * _s;

		return out;
	}

	//vec3 = vec3 / float
	Vec3 Vec3::operator/(const float _s)const
	{
		Vec3 out;
		out.m_x = this->m_x / _s;
		out.m_y = this->m_y / _s;
		out.m_z = this->m_z / _s;
		
		return out;
	}

	//vec3 += float
	Vec3 &Vec3::operator +=(const float _s) {
		this->m_x += _s;
		this->m_y += _s;
		this->m_z += _s;

		return *this;
	}

	//vec3 -= float
	Vec3 &Vec3::operator -=(const float _s) {
		this->m_x -= _s;
		this->m_y -= _s;
		this->m_z -= _s;

		return *this;
	}

	//vec3 *= float
	Vec3 &Vec3::operator *=(const float _s) {
		this->m_x *= _s;
		this->m_y *= _s;
		this->m_z *= _s;

		return *this;
	}

	//vec3 /= float
	Vec3 &Vec3::operator /=(const float _s) {
		this->m_x /= _s;
		this->m_y /= _s;
		this->m_z /= _s;

		return *this;
	}

	//-------------------------------------
	//���g�̃x�N�g���̒�����Ԃ�

	float Vec3::Length()const
	{
		return sqrtf((m_x*m_x) + (m_y*m_y) + (m_z*m_z));
	}

	//-----------------------------------------------
	//�x�N�g���̐��K��
	//�x�N�g���̒�����0�̏ꍇ���K���o���Ȃ��̂�assert

	void Vec3::Normalize()
	{
		float length = this->Length();
		assert(length);
		m_x /= length;
		m_y /= length;
		m_z /= length;
	}

	//-------------------------------------
	//�x�N�g���̊O�όv�Z

	Vec3 Vec3::Cross(const Vec3 &_v1, const Vec3 &_v2)
	{
		Vec3 out;
		out.m_x = _v1.m_y*_v2.m_z - _v1.m_z*_v2.m_y;
		out.m_y = _v1.m_z*_v2.m_x - _v1.m_x*_v2.m_z;
		out.m_z = _v1.m_x*_v2.m_y - _v1.m_y*_v2.m_x;

		return out;
	}

}