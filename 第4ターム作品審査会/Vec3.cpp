#include"Vec3.h"
#include<math.h>

namespace oka {

	//-------------------------------------
	//デフォルトコンストラクタ

	Vec3::Vec3():
		m_x(0), m_y(0), m_z(0)
	{}

	//-------------------------------------
	//引数付きコンストラクタ
	//引数として受け取った値でメンバを初期化

	Vec3::Vec3(const float _x, const float _y, const float _z):
		m_x(_x), m_y(_y), m_z(_z)
	{}

	//-------------------------------------
	//演算子のオーバーロード

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
	//自身のベクトルの長さを返す

	float Vec3::length()const
	{
		return sqrtf((m_x*m_x) + (m_y*m_y) + (m_z*m_z));
	}






}