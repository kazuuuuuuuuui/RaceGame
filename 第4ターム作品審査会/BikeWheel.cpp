#include<vector>
#include"BikeWheel.h"
#include"Vec3.h"
#include"Mat4×4.h"
#include"glut.h"

void BikeWheel::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		//回転処理
		//static float angle = 0;

		//後輪
		glPushMatrix();
		{
			//angle -= m_wheelSpeed;
			//angle *= 0.98f;

			//angleの値を-10000～0で扱うため
			/*if (angle < -200.f)
			{
				angle = 0.f;
			}*/

			oka::Mat4x4 scale = oka::Mat4x4::Scale(m_transform.GetScale());

			//オフセット
			oka::Mat4x4 offSet = oka::Mat4x4::Translate(m_transform.GetPosition());

			m_matrix = m_matrix * offSet * scale;

			glMultMatrixf((GLfloat*)&m_matrix);

			auto v = m_model.m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*v));

			auto n = m_model.m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*n));

			auto i = m_model.m_index.begin();

			float dd[] = { 0.00, 0.00, 0.00, 1 };
			glMaterialfv(GL_FRONT, GL_DIFFUSE, dd);

			glDrawElements(GL_TRIANGLES, m_model.m_indeces * 3, GL_UNSIGNED_SHORT, &(*i));

		}
		glPopMatrix();
	}
	glPopAttrib();
}