#include"Mat4×4.h"

//ビルボード行列
glm::mat4 BillboardMatrix;

namespace oka
{

	//-------------------------------------
	//コンストラクタ
	//引数で各行・列の要素を決定する

	Mat4x4::Mat4x4(
		const float _0, const float _1, const float _2, const float _3,
		const float _4, const float _5, const float _6, const float _7,
		const float _8, const float _9, const float _10,const float _11,
		const float _12,const float _13,const float _14,const float _15)
	{
		m_value[0] = _0; m_value[1] = _1; m_value[2] = _2; m_value[3] = _3;
		m_value[4] = _4; m_value[5] = _5; m_value[6] = _6; m_value[7] = _7;
		m_value[8] = _8; m_value[9] = _9; m_value[10] = _10; m_value[11] = _11;
		m_value[12] = _12; m_value[13] = _13; m_value[14] = _14; m_value[15] = _15;
	};


	//-------------------------------------
	//単位行列の取得

	Mat4x4 Mat4x4::IndentityMatrix()
	{
		Mat4x4 indentityMat = Mat4x4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		return indentityMat;
	}

	//-------------------------------------
	//モデル行列の設定
	
	///平行移動行列
	Mat4x4 Mat4x4::Translate(const Vec3 _t)
	{
		Mat4x4 translate = Mat4x4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			_t.m_x, _t.m_y, _t.m_z, 1);

			return translate;
	}

	///回転行列
	//引数の_rは"ラジアン"管理

	//x軸回転
	Mat4x4 Mat4x4::RotateX(const float _r)
	{
		Mat4x4 rotateX = Mat4x4(
			1, 0, 0, 0,
			0, cosf(_r), sinf(_r), 0,
			0, -sinf(_r), cos(_r), 0,
			0, 0, 0, 1);

		return rotateX;
	}

	//y軸回転
	Mat4x4 Mat4x4::RotateY(const float _r)
	{
		Mat4x4 rotateY = Mat4x4(
			cosf(_r), 0, -sinf(_r), 0,
			0, 1, 0, 0,
			sinf(_r), 0, cos(_r), 0,
			0, 0, 0, 1);

		return rotateY;
	}

	//z軸回転
	Mat4x4 Mat4x4::RotateZ(const float _r)
	{
		Mat4x4 rotateZ = Mat4x4(
			cosf(_r), sinf(_r), 0, 0,
			-sinf(_r), cosf(_r), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		return rotateZ;
	}


	///スケーリング行列
	Mat4x4 Mat4x4::Scale(const Vec3 _s)
	{
		Mat4x4 scale = Mat4x4(
			_s.m_x, 0, 0, 0,
			0, _s.m_y, 0, 0,
			0, 0, _s.m_z, 0,
			0, 0, 0, 1);

		return scale;
	}

	//-------------------------------------
	//透視射影行列の設定

	Mat4x4 Mat4x4::Perspective(const float _fovy, const float _aspect, const float _zNear, const float _zFar)
	{
		Mat4x4 perspective = Mat4x4(
			(1 / tanf(_fovy / 2)) / _aspect, 0, 0, 0,
			0, 1 / tanf(_fovy / 2), 0, 0,
			0, 0, (_zFar + _zNear) / (_zNear - _zFar), -1,
			0, 0, 2 * _zFar*_zNear / (_zNear - _zFar), 0
			);

		return perspective;
	}

	//-------------------------------------
	//正射影行列の設定

	Mat4x4 Mat4x4::Ortho(const float _left, const float _right, const float _bottom, const float _top, const float _zNear, const float _zFar)
	{
		Mat4x4 ortho = Mat4x4(
			2 / (_right - _left), 0, 0, 0,
			0, 2 / (_top - _bottom), 0, 0,
			0, 0, -2 / (_zFar - _zNear), 0,
			-(_right + _left) / (_right - _left), -(_top + _bottom) / (_top - _bottom), -(_zFar + _zNear) / (_zFar - _zNear), 1
			);

		return ortho;
	}

	//-------------------------------------
	//演算子のオーバーロード

	Mat4x4 Mat4x4::operator*(const Mat4x4 &_m)const
	{
		Mat4x4 out;

		out.m_value[0] = this->m_value[0] * _m.m_value[0] + this->m_value[4] * _m.m_value[1] + this->m_value[8] * _m.m_value[2] + this->m_value[12] * _m.m_value[3];
		out.m_value[1] = this->m_value[1] * _m.m_value[0] + this->m_value[5] * _m.m_value[1] + this->m_value[9] * _m.m_value[2] + this->m_value[13] * _m.m_value[3];
		out.m_value[2] = this->m_value[2] * _m.m_value[0] + this->m_value[6] * _m.m_value[1] + this->m_value[10] * _m.m_value[2] + this->m_value[14] * _m.m_value[3];
		out.m_value[3] = this->m_value[3] * _m.m_value[0] + this->m_value[7] * _m.m_value[1] + this->m_value[11] * _m.m_value[2] + this->m_value[15] * _m.m_value[3];
		out.m_value[4] = this->m_value[0] * _m.m_value[4] + this->m_value[4] * _m.m_value[5] + this->m_value[8] * _m.m_value[6] + this->m_value[12] * _m.m_value[7];
		out.m_value[5] = this->m_value[1] * _m.m_value[4] + this->m_value[5] * _m.m_value[5] + this->m_value[9] * _m.m_value[6] + this->m_value[13] * _m.m_value[7];
		out.m_value[6] = this->m_value[2] * _m.m_value[4] + this->m_value[6] * _m.m_value[5] + this->m_value[10] * _m.m_value[6] + this->m_value[14] * _m.m_value[7];
		out.m_value[7] = this->m_value[3] * _m.m_value[4] + this->m_value[7] * _m.m_value[5] + this->m_value[11] * _m.m_value[6] + this->m_value[15] * _m.m_value[7];
		out.m_value[8] = this->m_value[0] * _m.m_value[8] + this->m_value[4] * _m.m_value[9] + this->m_value[8] * _m.m_value[10] + this->m_value[12] * _m.m_value[11];
		out.m_value[9] = this->m_value[1] * _m.m_value[8] + this->m_value[5] * _m.m_value[9] + this->m_value[9] * _m.m_value[10] + this->m_value[13] * _m.m_value[11];
		out.m_value[10] = this->m_value[2] * _m.m_value[8] + this->m_value[6] * _m.m_value[9] + this->m_value[10] * _m.m_value[10] + this->m_value[14] * _m.m_value[11];
		out.m_value[11] = this->m_value[3] * _m.m_value[8] + this->m_value[7] * _m.m_value[9] + this->m_value[11] * _m.m_value[10] + this->m_value[15] * _m.m_value[11];
		out.m_value[12] = this->m_value[0] * _m.m_value[12] + this->m_value[4] * _m.m_value[13] + this->m_value[8] * _m.m_value[14] + this->m_value[12] * _m.m_value[15];
		out.m_value[13] = this->m_value[1] * _m.m_value[12] + this->m_value[5] * _m.m_value[13] + this->m_value[9] * _m.m_value[14] + this->m_value[13] * _m.m_value[15];
		out.m_value[14] = this->m_value[2] * _m.m_value[12] + this->m_value[6] * _m.m_value[13] + this->m_value[10] * _m.m_value[14] + this->m_value[14] * _m.m_value[15];
		out.m_value[15] = this->m_value[3] * _m.m_value[12] + this->m_value[7] * _m.m_value[13] + this->m_value[11] * _m.m_value[14] + this->m_value[15] * _m.m_value[15];

		return out;
	}

}
