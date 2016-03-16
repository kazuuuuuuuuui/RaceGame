#ifndef MATERIAL_H_
#define MATERIAL_H_

#include"glut.h"

class Material{
public:
	GLfloat m_ambient[4];
	GLfloat m_diffuse[4];
	GLfloat m_specular[4];
	GLfloat m_shininess;

	void setMaterial();
};

extern Material white_plastic;
extern Material ruby;


#endif