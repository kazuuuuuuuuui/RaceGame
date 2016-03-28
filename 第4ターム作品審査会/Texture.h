#ifndef OKA_TEXTURE_H_
#define OKA_TEXTURE_H_

#include"GameObject.h"
#include"Vec3.h"
#include"BmpImage.h"
#include"glm\glm.hpp"

namespace oka
{
	class Texture :public GameObject
	{
	public:
		unsigned int m_handle;
		float m_width;
		float m_height;
		Vec3 m_color;
		float m_alpha;

		void Update(){ m_flame++; };
		void Draw();
		void FadeOut();
		void SetColor(const oka::Vec3 _color);

		Texture(const char *_fileName, float _width, float _height, glm::vec2 _position):
			m_handle (oka::LoadImage4f(_fileName)),
			m_width(_width),m_height(_height),
			m_color(oka::Vec3(1.0f, 1.0f, 1.0f)),
			m_alpha(1.0f)
			{
				const float z = 0.0f;//âúçsÇÕïKÇ∏ÇO
				m_transform.SetPosition(oka::Vec3(_position.x, _position.y,z));
			}
	};
}

#endif