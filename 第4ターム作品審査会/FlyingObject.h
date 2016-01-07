#pragma once

#include"glm\glm.hpp"

//-------------------------------

class FlyingObject {
public:
	glm::vec3 m_position;
	glm::vec3 m_rotate;//単位はラジアン
	glm::vec3 m_scale;
	glm::vec3 m_speed;
	glm::vec3 m_accel;


	//初期化リストで各メンバ初期化
	FlyingObject() :
		m_position(0, 0, 0),
		m_rotate(0, 0, 0),
		m_scale(1, 1, 1),
		m_speed(0, 0, 0),
		m_accel(0, 0, 0)
	{};

	virtual void draw() = 0;

};

