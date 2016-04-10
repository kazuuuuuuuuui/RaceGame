#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<Windows.h>

#include"Course.h"
#include"CheckPoint.h"
#include"ItemManager.h"

#include<stdlib.h>
#include"BmpImage.h"


//-------------------------------------
//コンストラクタ
//コースに使う画像の読み込みと画像データから
//コースデータのバッファを作成する

Course::Course()
{
	m_name = nullptr;

	m_width = 0;
	m_height = 0;//
	m_depth = 0;

	m_bgm = 0;

	//背景色初期化
	oka::Vec3 color;
	color.m_x = 77.0f / 255.0f;
	color.m_y = 180.0f / 255.0f;
	color.m_z = 232.0f / 255.0f;
	m_backgroundColor = color;

	//頂点データ
	SetVertex();

	//インデックスデータ
	SetIndex();
	
	//法線データ
	SetNormal();

	//uvデータ
	SetTex();

	//test
	SetHeight("bmp/test.bmp");
}

//------------------------
//コースの頂点データの生成

void Course::SetVertex()
{
	for (int z = 0; z < COURSE_HEIGHT; z++)
	{
		for (int x = 0; x < COURSE_WIDTH; x++)
		{
			m_vertex.push_back(oka::Vec3(x, 0, -z));
		}
	}

	m_vertices = m_vertex.size();

}

//-------------------------------------
//コースのインデックスデータの生成

void Course::SetIndex()
{
	for (int z = 0; z < (COURSE_HEIGHT - 1); z++)
	{
		for (int x = 0; x < (COURSE_WIDTH - 1); x++)
		{
			m_index.push_back(0 + x + COURSE_HEIGHT * z);
			m_index.push_back(COURSE_WIDTH + x + COURSE_HEIGHT * z);
			m_index.push_back(1 + x + COURSE_HEIGHT * z);

			m_index.push_back(1 + x + COURSE_HEIGHT * z);
			m_index.push_back(COURSE_WIDTH + x + COURSE_HEIGHT * z);
			m_index.push_back((COURSE_WIDTH + 1) + x + COURSE_HEIGHT * z);
		}
	}

	m_indeces = m_index.size();

}

//-------------------------------------
//法線の計算
//三角ポリゴン2枚を1組として外積計算

void Course::SetNormal()
{
	for (int z = 0; z < COURSE_HEIGHT; z++)
	{
		for (int x = 0; x < COURSE_WIDTH; x++)
		{
			m_normal.push_back(oka::Vec3(0, 1, 0));
		}
	}
	//for (int z = 0; z < (COURSE_HEIGHT - 1); z++)
	//{
	//	for (int x = 0; x < (COURSE_WIDTH - 1); x++)
	//	{
	//		oka::Vec3 v0 = m_vertex[0 + x + COURSE_HEIGHT * z];
	//		oka::Vec3 v1 = m_vertex[COURSE_WIDTH + x + COURSE_HEIGHT * z];
	//		oka::Vec3 v2 = m_vertex[1 + x + COURSE_HEIGHT * z];

	//		oka::Vec3 v01 = v1 - v0;
	//		oka::Vec3 v02 = v2 - v0;

	//		//面の法線
	//		oka::Vec3 normal = oka::Vec3::Cross(v01,v02);
	//		normal.Normalize();
	//		m_normal.push_back(normal);
	//		m_normal.push_back(normal);
	//		m_normal.push_back(normal);

	//		v0 = m_vertex[1 + x + COURSE_HEIGHT * z];
	//		v1 = m_vertex[COURSE_WIDTH + x + COURSE_HEIGHT * z];
	//		v2 = m_vertex[(COURSE_WIDTH + 1) + x + COURSE_HEIGHT * z];

	//		v01 = v1 - v0;
	//		v02 = v2 - v0;

	//		normal = oka::Vec3::Cross(v01, v02);
	//		normal.Normalize();
	//		m_normal.push_back(normal);
	//		m_normal.push_back(normal);
	//		m_normal.push_back(normal);

	//	}
	//}
}

//----------------
//uv座標の設定

void Course::SetTex()
{
	for (int v = COURSE_HEIGHT; v > 0; v--)
	{
		for (int u = 0; u < COURSE_WIDTH; u++)
		{
			glm::vec2 t;
			t.x = (u / 1.0f) / COURSE_WIDTH;//u
			t.y = (v / 1.0f) / COURSE_HEIGHT;//v

			m_tex.push_back(t);

		}
	}
}

//-------------------------------------
//拡張子bmpからコースの各頂点のY座標を設定する

void Course::SetHeight(const char *_fileName)
{
	FILE *fp;
	fp = fopen(_fileName, "rb");

	assert(fp != NULL);

	BITMAPFILEHEADER bh;
	fread(&bh, sizeof(BITMAPFILEHEADER), 1, fp);

	BITMAPINFOHEADER bih;
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, fp);

	int imageSize = bih.biWidth * bih.biHeight * sizeof(oka::RGB);

	oka::RGB *pixels = (oka::RGB*)malloc(imageSize);

	pixels = (oka::RGB*)malloc(imageSize);

	fread(pixels, imageSize, 1, fp);

	fclose(fp);

	//ピクセル単位でRとBを逆転させる
	for (int i = 0; i < bih.biWidth * bih.biHeight; i++)
	{
		unsigned char tmp;
		tmp = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = tmp;
	}

	//ピクセル単位で上下反転
	/*for (int i = 0; i < bih.biWidth; i++)
	{
		for (int n = 0; n < bih.biHeight / 2; n++)
		{
			oka::RGB temp = pixels[bih.biWidth * n + i];
			pixels[bih.biWidth * n + i] = pixels[bih.biWidth*(bih.biHeight - n - 1) + i];
			pixels[bih.biWidth*(bih.biHeight - n - 1) + i] = temp;
		}
	}*/

	//Y座標の設定
	for (int z = 0; z < bih.biHeight; z++)
	{
		for (int x = 0; x < bih.biWidth; x++)
		{
			float height = (pixels[z*bih.biWidth + x].r + pixels[z*bih.biWidth + x].g + pixels[z*bih.biWidth + x].b)/3.0f;
			
			height /= 255.0f;//0.0～1.0f;

			//test
			height = 1.0f - height;

			m_vertex[z*bih.biWidth + x].m_y = height;
		}
	}

}

//-------------------------------------
//拡張子bmpからコース用のバッファを作製する

void Course::MakeBuffer(const char *_fileName)
{
	FILE *pBinMapFile;
	pBinMapFile = fopen(_fileName, "rb");

	assert(pBinMapFile != NULL);

	BITMAPFILEHEADER bh;
	fread(&bh, sizeof(BITMAPFILEHEADER), 1, pBinMapFile);

	BITMAPINFOHEADER bih;
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, pBinMapFile);

	//画像の縦横情報の取得
	m_width = bih.biWidth;
	m_height = bih.biHeight;

	int imageSize = bih.biWidth * bih.biHeight * sizeof(oka::RGB);

	oka::RGB *pixels = (oka::RGB*)malloc(imageSize);

	pixels = (oka::RGB*)malloc(imageSize);

	fread(pixels, imageSize, 1, pBinMapFile);

	fclose(pBinMapFile);

	//ピクセル単位でRとBを逆転させる
	for (int i = 0; i < bih.biWidth * bih.biHeight; i++)
	{
		unsigned char tmp;
		tmp = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = tmp;
	}

	//ピクセル単位で上下反転
	for (int i = 0; i < bih.biWidth; i++)
	{
		for (int n = 0; n < bih.biHeight / 2; n++)
		{
			oka::RGB temp = pixels[bih.biWidth * n + i];
			pixels[bih.biWidth * n + i] = pixels[bih.biWidth*(bih.biHeight - n - 1) + i];
			pixels[bih.biWidth*(bih.biHeight - n - 1) + i] = temp;
		}
	}

	//コース判定用のバッファ作成
	for (int i = 0; i < bih.biHeight; i++) {
		for (int t = 0; t < bih.biWidth; t++) {

			//白なら道
			if (pixels[t + i*bih.biWidth].r == 255 &&
				pixels[t + i*bih.biWidth].g == 255 &&
				pixels[t + i*bih.biWidth].b == 255)
			{

				m_buffer[i][t] = PATH;
			}

			//黒ならダート
			else if (pixels[t + i*bih.biWidth].r == 0 &&
				pixels[t + i*bih.biWidth].g == 0 &&
				pixels[t + i*bih.biWidth].b == 0)
			{
				m_buffer[i][t] = DART;
			}

			//赤ならスタート
			else if (pixels[t + i*bih.biWidth].r == 255 &&
				pixels[t + i*bih.biWidth].g == 0 &&
				pixels[t + i*bih.biWidth].b == 0) {

				m_buffer[i][t] = START;
			}

			//青ならゴール
			else if (pixels[t + i*bih.biWidth].r == 0 &&
				pixels[t + i*bih.biWidth].g == 0 &&
				pixels[t + i*bih.biWidth].b == 255)
			{
				m_buffer[i][t] = GOAL;
			}

			//緑ならアイテムの場所
			else if (pixels[t + i*bih.biWidth].r == 0 &&
				pixels[t + i*bih.biWidth].g == 255 &&
				pixels[t + i*bih.biWidth].b == 0)
			{
				m_buffer[i][t] = ITEMPOSITION;
			}
		}

	}

	free(pixels);

}

//-------------------------------------
//






//-------------------------------------
//各コース全体の描画

void Course::Draw(){

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_handle);

		glPushMatrix();
		{
			auto v = m_vertex.begin();
			glVertexPointer(3, GL_FLOAT, 0, &(*v));

			auto n = m_normal.begin();
			glNormalPointer(GL_FLOAT, 0, &(*n));

			auto t = m_tex.begin();
			glTexCoordPointer(2, GL_FLOAT, 0, &(*t));

			auto i = m_index.begin();

			glDrawElements(GL_TRIANGLES, m_indeces, GL_UNSIGNED_SHORT, &(*i));

		}
		glPopMatrix();
	}
	glPopAttrib();
}

//-------------------------------------
//コース上に魔石を配置する
//画像左上から右下に向かって読んでいく

void Course::SetItem()
{
	for (int i = 0; i < COURSE_HEIGHT; i++){
		for (int t = 0; t < COURSE_WIDTH; t++){

			if (ITEMPOSITION == m_buffer[i][t]){

				//取り敢えず
				oka::Vec3 position;
				position.m_x = t;
				position.m_y = 0.5f;
				position.m_z = i - COURSE_HEIGHT;

				ItemManager::GetInstance()->m_item[itemNum]->m_transform.SetPosition(position);

				itemNum++;

			}

		}
	}

}

//-------------------------------------
//選択されたコースにチェックポイントを配置する
//チェックポイントの座標は外部テキストファイルに保管

void Course::SetCheckPoint(const char *_txtName) 
{

	FILE *fp = fopen(_txtName, "r");
	assert(fp != nullptr);

	for (int i = 0; i < Course::checkPointNum; i++)
	{
		oka::Vec3 position;
		fscanf(fp, "(%f,%f,%f)", &position.m_x, &position.m_y, &position.m_z);
		fscanf(fp, "%*c"); //改行文字読み飛ばし

		m_checkPoint[i].m_position = position;

	}

}

//-------------------------------------
//選択されたコースにAI制御用のポイントを配置する
//チェックポイントの座標は外部テキストファイルに保管

void Course::SetAimPoint(const char *_txtName) 
{
	FILE *fp = fopen(_txtName, "r");
	assert(fp != nullptr);

	for (int i = 0; i < Course::aimPointNum; i++)
	{
		oka::Vec3 position;
		fscanf(fp, "(%f,%f,%f)", &position.m_x, &position.m_y, &position.m_z);
		fscanf(fp, "%*c"); //改行文字読み飛ばし

		m_aimPoint[i].m_position = position;

	}

}
