#include"Vec3.h"

namespace oka
{
	class Transform
	{
	private:
		Vec3 m_position;
		Vec3 m_lastPosition;
		Vec3 m_rotate;
		Vec3 m_scale;

	public:
		Transform();

		void SetPosition(const Vec3 _position) { m_position = _position; }
		void SetPositionX(const float _positionX) { m_position.m_x = _positionX; }
		void SetPositionY(const float _positionY) { m_position.m_y = _positionY; }
		void SetPositionZ(const float _positionZ) { m_position.m_z = _positionZ; }

		void SetRotation(const Vec3 _rotate) { m_rotate = _rotate; }
		void SetRotationX(const float _rotateX) { m_rotate.m_x = _rotateX; }
		void SetRotationY(const float _rotateY) { m_rotate.m_y = _rotateY; }
		void SetRotationZ(const float _rotateZ) { m_rotate.m_z = _rotateZ; }

		void SetScale(const Vec3 _scale) { m_scale = _scale; }

		Vec3 GetPosition()const { return m_position; }
		Vec3 GetRotation()const { return m_rotate; }
		Vec3 GetScale()const { return m_scale; }

	



	};

}