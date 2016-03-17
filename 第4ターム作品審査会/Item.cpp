#define _USE_MATH_DEFINES
#include<math.h>
#include"Item.h"
#include"Character.h"
#include"CourseFlag.h"
#include"ImageManager.h"
#include"SoundManager.h"
#include"glut.h"

//debug
//アイテムの影に使う
void Circle2DFill(float radius, int x, int y)
{
	for (float th1 = 0.0; th1 <= 360.0; th1 = th1 + 1.0)
	{
		float th2 = th1 + 10.0;
		float th1_rad = th1 / 180.0 * M_PI;
		float th2_rad = th2 / 180.0 * M_PI;

		float x1 = radius * cos(th1_rad);
		float y1 = radius * sin(th1_rad);
		float x2 = radius * cos(th2_rad);
		float y2 = radius * sin(th2_rad);

		glBegin(GL_TRIANGLES);
		glVertex2f(x, y);
		glVertex2f(x1 + x, y1 + y);
		glVertex2f(x2 + x, y2 + y);
		glEnd();
	}
}

Item *item[SET_ITEM_NUMBER] = { nullptr };

//アイテムの添え字に使う
int itemNum = 0;

//-------------------------------------
//アイテムの更新

void Item::update(){

	m_flame++;

	//動き
	move();

	//アイテムの再出現
	if (0 == m_flame % (60 * 10))
	{
		reCreateItem();
	}

	//取られたかの判定
	for (unsigned int i = 0; i < character.size(); i++)
	{
		if (true == m_isActive && checkIsGotten(character[i]->m_transform.GetPosition()))
		{

			m_isActive = false;


			//所持アイテムが3つ以下だったらアイテムを所持させる
			if (character[i]->hasItemNumber() < HAS_ITEM_MAX)
			{
				//キャラクターに今取得したアイテムを持たせる
				character[i]->m_hasItem.push_back(m_type);

				//プレイヤーが取得したときのみ効果音を鳴らす
				if (player1 == character[i])
				{
					oka::SoundManager::getInstance()->Play("getItem");
				}

			}
		}

	}

}

//-------------------------------------
//魔石の動き
//上下に揺らす(仮)

void Item::move(){

	//取り敢えず
	static float ag = 0.f;
	ag += 0.001;

	//0.5～1
	m_transform.SetPositionY(((sin(ag) + 1) / 4) + 0.5f);

}

//-------------------------------------
//魔石の描画
//スフィアマッピングをするための拾い物関数なので後で要理解


void Item::draw()
{

	if (true == m_isActive){

		//タイプによって使用するテクスチャを変える

		switch (m_type){
		case FIRE:

			//glBindTexture(GL_TEXTURE_2D, ItemFire);
			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("ItemFire"));


			break;

		case BLIZZARD:

			glBindTexture(GL_TEXTURE_2D, oka::ImageManager::GetInstance()->GetHandle("ItemBlizzard"));

			break;

		}

		glPushMatrix();
		{
			glTranslatef(m_transform.GetPosition().m_x, m_transform.GetPosition().m_y, m_transform.GetPosition().m_z);
			glRotatef(0, m_transform.GetRotation().m_x, m_transform.GetRotation().m_y, m_transform.GetRotation().m_z);
			glScalef(m_transform.GetScale().m_x, m_transform.GetScale().m_y, m_transform.GetScale().m_z);

			glColor3f(1, 1, 1);

			double s, t0, t1, r0, r1, th0, th1, phi;
			double p[2][3];

			for (int j = 0; j < ITEM_STACK; j++){
				t0 = (double)j / (double)ITEM_STACK;
				t1 = (double)(j + 1) / (double)ITEM_STACK;
				th0 = M_PI * t0;
				th1 = M_PI * t1;
				r0 = ITEM_RADIUS * sin(th0);
				r1 = ITEM_RADIUS * sin(th1);
				p[0][2] = ITEM_RADIUS * cos(th0);
				p[1][2] = ITEM_RADIUS * cos(th1);

				t0 = (1.0 - t0) * ITEM_REPEAT_T;
				t1 = (1.0 - t1) * ITEM_REPEAT_T;

				glEnable(GL_TEXTURE_2D);

				glBegin(GL_QUAD_STRIP);
				for (int i = 0; i <= ITEM_SLICE; i++){
					s = (double)i / (double)ITEM_SLICE;
					phi = 2.0 * M_PI * s;
					p[0][0] = -r0 * cos(phi);
					p[0][1] = -r0 * sin(phi);
					p[1][0] = -r1 * cos(phi);
					p[1][1] = -r1 * sin(phi);

					s *= ITEM_REPEAT_S;

					glTexCoord2d(s, t0);
					glNormal3dv(p[0]);
					glVertex3dv(p[0]);

					glTexCoord2d(s, t1);
					glNormal3dv(p[1]);
					glVertex3dv(p[1]);
				}
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}

		}
		glPopMatrix();

		//アイテムの影
		glPushMatrix();
		{
			glTranslatef(m_transform.GetPosition().m_x, 0.1, m_transform.GetPosition().m_z);
			glRotatef(90, 1, 0, 0);
			glColor3f(110.f / 255.f, 110.f / 255.f, 110.f / 255.f);
			Circle2DFill(0.3, 0, 0);
		}
		glPopMatrix();

	}
}


//-------------------------------------
//アイテムの再出現

void Item::reCreateItem(){

	if (false == m_isActive){
		m_type = rand() % ITEM_TYPE_MAX;
		m_isActive = true;
	}

}

//-------------------------------------
//プレイヤーによって取得されたかを判定する

bool Item::checkIsGotten(oka::Vec3 _position){

	//プレイヤーと魔石との距離
	glm::vec3 distance;
	distance.x = (m_transform.GetPosition().m_x - _position.m_x);
	distance.y = (m_transform.GetPosition().m_y - _position.m_y);
	distance.z = (m_transform.GetPosition().m_z - _position.m_z);

	float length = sqrt(distance.x*distance.x + distance.y*distance.y + distance.z*distance.z);

	if (length < 1.5f){
		return true;
	}
	else{
		return false;
	}

}