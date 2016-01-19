
//スフィアマッピング用に
#define MAGICSTONR_RADIUS (0.4f)
#define MAGICSTONR_SLICE (10)
#define MAGICSTONR_STACK (10)
#define MAGICSTONR_REPEAT_S (1)
#define MAGICSTONR_REPEAT_T (1)


#define _USE_MATH_DEFINES
#include<math.h>
#include"MagicStone.h"
#include"Player.h"
#include"CourseFlag.h"
#include"glut.h"

//debug
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


MagicStone *magicStone[SET_MAGICSTONE_NUMBER] = { nullptr };

//魔石(アイテム)のテクスチャを格納する
GLuint fire_handle = 0;//ファイア
GLuint blizzard_handle = 0;//ブリザド
GLuint haste_handle = 0;//ヘイスト


//-------------------------------------
//魔石の更新

void MagicStone::update(){

	//動き
	move();

	if (false == m_isGotten && checkIsGotten()){
		m_isGotten = true;
		player->m_hasMagicStone.push_back(this);

	}

	if (m_isGotten == true){

		this->m_position.x = player->m_position.x + sin(player->m_rotate.y) * 2;
		this->m_position.z = player->m_position.z + cos(player->m_rotate.y) * 2;

	}

}

//-------------------------------------
//魔石の動き
//上下に揺らす(仮)

void MagicStone::move(){

	//取り敢えず
	static float ag = 0.f;
	ag += 0.001;

	//0.5～1
	m_position.y = ((sin(ag) + 1) / 4) + 0.5f;

}

//-------------------------------------
//魔石の描画
//スフィアマッピングをするための拾い物関数なので後で要理解

void MagicStone::draw(){

	//タイプによって使用するテクスチャを変える

	switch (m_type){
	case FIRE:

		glBindTexture(GL_TEXTURE_2D, fire_handle);

		break;

	case BLIZZARD:

		glBindTexture(GL_TEXTURE_2D, blizzard_handle);

		break;



	}

	glPushMatrix();
	{
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(0, m_rotate.x, m_rotate.y, m_rotate.z);
		glScalef(m_scale.x, m_scale.y, m_scale.z);

		glColor3f(1, 1, 1);

		double s, t0, t1, r0, r1, th0, th1, phi;
		double p[2][3];

		for (int j = 0; j < MAGICSTONR_STACK; j++){
			t0 = (double)j / (double)MAGICSTONR_STACK;
			t1 = (double)(j + 1) / (double)MAGICSTONR_STACK;
			th0 = M_PI * t0;
			th1 = M_PI * t1;
			r0 = MAGICSTONR_RADIUS * sin(th0);
			r1 = MAGICSTONR_RADIUS * sin(th1);
			p[0][2] = MAGICSTONR_RADIUS * cos(th0);
			p[1][2] = MAGICSTONR_RADIUS * cos(th1);

			t0 = (1.0 - t0) * MAGICSTONR_REPEAT_T;
			t1 = (1.0 - t1) * MAGICSTONR_REPEAT_T;

			glEnable(GL_TEXTURE_2D);

			glBegin(GL_QUAD_STRIP);
			for (int i = 0; i <= MAGICSTONR_SLICE; i++){
				s = (double)i / (double)MAGICSTONR_SLICE;
				phi = 2.0 * M_PI * s;
				p[0][0] = -r0 * cos(phi);
				p[0][1] = -r0 * sin(phi);
				p[1][0] = -r1 * cos(phi);
				p[1][1] = -r1 * sin(phi);

				s *= MAGICSTONR_REPEAT_S;

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
		//0.49は後で修正
		glTranslatef(m_position.x, 0.1, m_position.z);
		glRotatef(90, 1, 0, 0);
		glColor3f(110.f / 255.f, 110.f / 255.f, 110.f / 255.f);
		Circle2DFill(0.3, 0, 0);
	}
	glPopMatrix();

}

//-------------------------------------
//プレイヤーによって取得されたかを判定する

bool MagicStone::checkIsGotten(){

	//プレイヤーと魔石との距離
	glm::vec3 distance;
	distance.x = (m_position.x - player->m_position.x);
	distance.y = (m_position.y - player->m_position.y);
	distance.z = (m_position.z - player->m_position.z);

	float length = sqrt(distance.x*distance.x + distance.y*distance.y + distance.z*distance.z);

	if (length < 1.f){
		return true;
	}
	else{
		return false;
	}

}