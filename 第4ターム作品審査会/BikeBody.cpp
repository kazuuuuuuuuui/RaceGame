#include"BikeBody.h"
#include"Mat4~4.h"
#include"glut.h"

//----------------
//Ô‘Ì•”•ª‚Ì•`‰æ

void BikeBody::Draw()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		glPushMatrix();
		{
			//s—ñ“K‰
			glMultMatrixf((GLfloat*)&m_matrix);

			auto v = m_model.m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*v));

			auto n = m_model.m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*n));

			auto i = m_model.m_index.begin();

			glDrawElements(GL_TRIANGLES, m_model.m_indeces * 3, GL_UNSIGNED_SHORT, &(*i));

		}
		glPopMatrix();

	}
	glPopAttrib();
}

//-----------------
//Ô‘Ì•”•ª‰e‚Ì•`‰æ

void BikeBody::DrawShadow()
{
	glColor3f(100.0f / 255.0f, 100.0f / 255.0f, 100.0f / 255.0f);

	glPushMatrix();
	{
		//s—ñŒvZ
		//glm::mat4 parentTranslate = glm::translate(glm::vec3(m_transform.GetPosition().m_x, 0.01f, m_transform.GetPosition().m_z));
		oka::Mat4x4 translate = oka::Mat4x4::Translate(oka::Vec3(m_transform.GetPosition().m_x, 0.01f, m_transform.GetPosition().m_z));

		//glm::mat4 parentRotate = glm::rotate(m_transform.GetRotation().m_y + m_crashRotate, glm::vec3(0, 1, 0));
		oka::Mat4x4 rotate = oka::Mat4x4::RotateY(m_transform.GetRotation().m_y/* + m_crashRotate*/);

		//glm::mat4 parentScale = glm::scale(glm::vec3(m_transform.GetScale().m_x, 0, m_transform.GetScale().m_z));
		oka::Mat4x4 scale = oka::Mat4x4::Scale(oka::Vec3(m_transform.GetScale().m_x, 0, m_transform.GetScale().m_z));

		m_matrix = translate * rotate * scale;

		//s—ñ“K‰
		glMultMatrixf((GLfloat*)&m_matrix);

		auto v = m_model.m_vertex.begin();
		glVertexPointer(3, GL_FLOAT, 0, &(*v));

		auto i = m_model.m_index.begin();

		glDrawElements(GL_TRIANGLES, m_model.m_indeces * 3, GL_UNSIGNED_SHORT, &(*i));

	}
	glPopMatrix();

}