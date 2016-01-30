#ifndef STROKESTRING_H_
#define STROKESTRING_H_

#include"glm\glm.hpp"

class StrokeString{
public:
	char *m_character;
	void *font;

	static void print(const char *_character, glm::vec3 _position, float _scale,glm::vec3 _color);
};

#endif
