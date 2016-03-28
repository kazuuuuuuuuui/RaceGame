#ifndef _OKA_STROKESTRING_H_
#define _OKA_STROKESTRING_H_

#include"Vec3.h"
#include"glm\glm.hpp"

namespace oka
{
	void SetLineWidth(const float _width);
	void SetDefaultLineWidth();
	void DrawString(const char *_str, const glm::vec2 _position, const float _scale, const oka::Vec3 _color, const float _width);

}

#endif
