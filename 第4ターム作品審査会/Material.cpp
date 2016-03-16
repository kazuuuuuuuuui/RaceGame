#include"Material.h"

//プラスチック(白)
Material white_plastic = {
	{ 0.0, 0.0, 0.0, 1.0 },
	{ 1, 0, 0, 1.0 },
	{ 0.70, 0.70, 0.70, 1.0 },
	32
};

Material ruby = {
	{ 0.1745, 0.01175, 0.01175, 1.0 },
	{ 0.61424, 0.04136, 0.04136, 1.0 },
	{ 0.727811, 0.626959, 0.626959, 1.0 },
	76.8
};


void Material::setMaterial(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, m_shininess);
}