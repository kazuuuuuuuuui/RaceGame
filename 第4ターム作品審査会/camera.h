#pragma once

#include"glm\glm.hpp"
#include"glut.h"

enum{
	TYPE_2D = 0,
	TYPE_3D
};


class Camera{
public:
	GLdouble m_angle;
	GLdouble m_aspect;
	GLdouble m_zNear;
	GLdouble m_zFar;
	glm::vec3 m_position;
	glm::vec3 m_rotate;
	glm::vec3 m_target;
	glm::vec3 m_up;

	Camera() :
		m_angle(60),
		m_aspect(1),
		m_zNear(0.1),
		m_zFar(1000),
		m_position(0, 0, 0),
		m_rotate(0, 0, 0),
		m_target(0, 0, 0),
		m_up(0, 1, 0)
	{};

	void update(const int _type);
	void setPosition(glm::vec3 _position){ m_position = _position; }
	void setTarget(glm::vec3 _target){ m_target = _target; }

};

extern Camera *camera;

