#ifndef _VEC3_H_
#define _VEC3_H_

namespace oka
{
	class Vec3 
	{
	public:

		float m_x;
		float m_y;
		float m_z;

		Vec3();
		Vec3(const float _x, const float _y, const float _z);
		~Vec3() {};

		float Length()const;
		void Normalize();
		static Vec3 Cross(const Vec3 &_v1, const Vec3 &_v2);
	
		Vec3 operator +(const Vec3 &_v)const;
		Vec3 operator -(const Vec3 &_v)const;
		Vec3 operator *(const Vec3 &_v)const;
		Vec3 operator /(const Vec3 &_v)const;

		Vec3 &operator +=(const Vec3 &_v);
		Vec3 &operator -=(const Vec3 &_v);
		Vec3 &operator /=(const Vec3 &_v);
		Vec3 &operator *=(const Vec3 &_v);

		Vec3 operator +(const float _s)const;
		Vec3 operator -(const float _s)const;
		Vec3 operator *(const float _s)const;
		Vec3 operator /(const float _s)const;

		Vec3 &operator +=(const float _s);
		Vec3 &operator -=(const float _s);
		Vec3 &operator *=(const float _s);
		Vec3 &operator /=(const float _s);
			
	};

} //namespace oka

#endif