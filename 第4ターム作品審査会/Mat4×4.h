#ifndef _OKA_MAT4X4_H_
#define _OKA_MAT4X4_H_

#include"Vec3.h"
#include"glm\gtc\matrix_transform.hpp"

namespace oka
{

	//-------------------------------------
	//４×４の行列クラス 各要素はfloat型

	class Mat4x4
	{
	public:
		Mat4x4(){};
		Mat4x4(const float _0, const float _1, const float _2, const float _3,
			   const float _4, const float _5, const float _6, const float _7, 
			   const float _8, const float _9, const float _10,const float _11,
			   const float _12,const float _13,const float _14,const float _15);

		static Mat4x4 IndentityMatrix();
		static Mat4x4 Translate(const Vec3 _t);
		static Mat4x4 RotateX(const float _r);
		static Mat4x4 RotateY(const float _r);
		static Mat4x4 RotateZ(const float _r);
		static Mat4x4 Scale(const Vec3 _s);
	
		static Mat4x4 Perspective(const float _fovy, const float _aspect, const float _zNear, const float _zFar);
		static Mat4x4 Ortho(const float _left, const float _right, const float _bottom, const float _top, const float _zNear, const float _zFar);

		Mat4x4 operator *(const Mat4x4 &_m)const;

		float m_value[16];

	};

}

//ビルボード行列
extern glm::mat4 BillboardMatrix;


#endif