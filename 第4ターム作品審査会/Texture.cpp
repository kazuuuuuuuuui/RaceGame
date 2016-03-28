#include"Texture.h"

namespace oka
{
	//-------------------------------------
	//自身のハンドルを四角板に張り付ける

	void Texture::Draw()
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBindTexture(GL_TEXTURE_2D, m_handle);

			glPushMatrix();
			{
				glTranslatef(m_transform.GetPosition().m_x, m_transform.GetPosition().m_y, m_transform.GetPosition().m_z);
				glRotatef(0, m_transform.GetRotation().m_x, m_transform.GetRotation().m_y, m_transform.GetRotation().m_z);
				glScalef(m_transform.GetScale().m_x, m_transform.GetScale().m_y, m_transform.GetScale().m_z);

				glColor4f(m_color.m_x, m_color.m_y, m_color.m_z, m_alpha);

				glBegin(GL_QUADS);
				{
					glTexCoord2f(0.f, 1.0f); glVertex2f(0.0f, 0.0f);
					glTexCoord2f(1.0f, 1.0f); glVertex2f(m_width, 0.0f);
					glTexCoord2f(1.0f, 0.0f); glVertex2f(m_width, m_height);
					glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, m_height);

				}
				glEnd();
			}
			glPopMatrix();
		}
		glPopAttrib();
	}

}//namespace oka