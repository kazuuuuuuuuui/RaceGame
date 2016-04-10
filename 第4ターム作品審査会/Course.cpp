#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<Windows.h>

#include"Course.h"
#include"CheckPoint.h"
#include"ItemManager.h"

#include<stdlib.h>
#include"BmpImage.h"


//-------------------------------------
//�R���X�g���N�^
//�R�[�X�Ɏg���摜�̓ǂݍ��݂Ɖ摜�f�[�^����
//�R�[�X�f�[�^�̃o�b�t�@���쐬����

Course::Course()
{
	m_name = nullptr;

	m_width = 0;
	m_height = 0;//
	m_depth = 0;

	m_bgm = 0;

	//�w�i�F������
	oka::Vec3 color;
	color.m_x = 77.0f / 255.0f;
	color.m_y = 180.0f / 255.0f;
	color.m_z = 232.0f / 255.0f;
	m_backgroundColor = color;

	//���_�f�[�^
	SetVertex();

	//�C���f�b�N�X�f�[�^
	SetIndex();
	
	//�@���f�[�^
	SetNormal();

	//uv�f�[�^
	SetTex();

	//test
	SetHeight("bmp/test.bmp");
}

//------------------------
//�R�[�X�̒��_�f�[�^�̐���

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
//�R�[�X�̃C���f�b�N�X�f�[�^�̐���

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
//�@���̌v�Z
//�O�p�|���S��2����1�g�Ƃ��ĊO�όv�Z

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

	//		//�ʂ̖@��
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
//uv���W�̐ݒ�

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
//�g���qbmp����R�[�X�̊e���_��Y���W��ݒ肷��

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

	//�s�N�Z���P�ʂ�R��B���t�]������
	for (int i = 0; i < bih.biWidth * bih.biHeight; i++)
	{
		unsigned char tmp;
		tmp = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = tmp;
	}

	//�s�N�Z���P�ʂŏ㉺���]
	/*for (int i = 0; i < bih.biWidth; i++)
	{
		for (int n = 0; n < bih.biHeight / 2; n++)
		{
			oka::RGB temp = pixels[bih.biWidth * n + i];
			pixels[bih.biWidth * n + i] = pixels[bih.biWidth*(bih.biHeight - n - 1) + i];
			pixels[bih.biWidth*(bih.biHeight - n - 1) + i] = temp;
		}
	}*/

	//Y���W�̐ݒ�
	for (int z = 0; z < bih.biHeight; z++)
	{
		for (int x = 0; x < bih.biWidth; x++)
		{
			float height = (pixels[z*bih.biWidth + x].r + pixels[z*bih.biWidth + x].g + pixels[z*bih.biWidth + x].b)/3.0f;
			
			height /= 255.0f;//0.0�`1.0f;

			//test
			height = 1.0f - height;

			m_vertex[z*bih.biWidth + x].m_y = height;
		}
	}

}

//-------------------------------------
//�g���qbmp����R�[�X�p�̃o�b�t�@���쐻����

void Course::MakeBuffer(const char *_fileName)
{
	FILE *pBinMapFile;
	pBinMapFile = fopen(_fileName, "rb");

	assert(pBinMapFile != NULL);

	BITMAPFILEHEADER bh;
	fread(&bh, sizeof(BITMAPFILEHEADER), 1, pBinMapFile);

	BITMAPINFOHEADER bih;
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, pBinMapFile);

	//�摜�̏c�����̎擾
	m_width = bih.biWidth;
	m_height = bih.biHeight;

	int imageSize = bih.biWidth * bih.biHeight * sizeof(oka::RGB);

	oka::RGB *pixels = (oka::RGB*)malloc(imageSize);

	pixels = (oka::RGB*)malloc(imageSize);

	fread(pixels, imageSize, 1, pBinMapFile);

	fclose(pBinMapFile);

	//�s�N�Z���P�ʂ�R��B���t�]������
	for (int i = 0; i < bih.biWidth * bih.biHeight; i++)
	{
		unsigned char tmp;
		tmp = pixels[i].r;
		pixels[i].r = pixels[i].b;
		pixels[i].b = tmp;
	}

	//�s�N�Z���P�ʂŏ㉺���]
	for (int i = 0; i < bih.biWidth; i++)
	{
		for (int n = 0; n < bih.biHeight / 2; n++)
		{
			oka::RGB temp = pixels[bih.biWidth * n + i];
			pixels[bih.biWidth * n + i] = pixels[bih.biWidth*(bih.biHeight - n - 1) + i];
			pixels[bih.biWidth*(bih.biHeight - n - 1) + i] = temp;
		}
	}

	//�R�[�X����p�̃o�b�t�@�쐬
	for (int i = 0; i < bih.biHeight; i++) {
		for (int t = 0; t < bih.biWidth; t++) {

			//���Ȃ瓹
			if (pixels[t + i*bih.biWidth].r == 255 &&
				pixels[t + i*bih.biWidth].g == 255 &&
				pixels[t + i*bih.biWidth].b == 255)
			{

				m_buffer[i][t] = PATH;
			}

			//���Ȃ�_�[�g
			else if (pixels[t + i*bih.biWidth].r == 0 &&
				pixels[t + i*bih.biWidth].g == 0 &&
				pixels[t + i*bih.biWidth].b == 0)
			{
				m_buffer[i][t] = DART;
			}

			//�ԂȂ�X�^�[�g
			else if (pixels[t + i*bih.biWidth].r == 255 &&
				pixels[t + i*bih.biWidth].g == 0 &&
				pixels[t + i*bih.biWidth].b == 0) {

				m_buffer[i][t] = START;
			}

			//�Ȃ�S�[��
			else if (pixels[t + i*bih.biWidth].r == 0 &&
				pixels[t + i*bih.biWidth].g == 0 &&
				pixels[t + i*bih.biWidth].b == 255)
			{
				m_buffer[i][t] = GOAL;
			}

			//�΂Ȃ�A�C�e���̏ꏊ
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
//�e�R�[�X�S�̂̕`��

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
//�R�[�X��ɖ��΂�z�u����
//�摜���ォ��E���Ɍ������ēǂ�ł���

void Course::SetItem()
{
	for (int i = 0; i < COURSE_HEIGHT; i++){
		for (int t = 0; t < COURSE_WIDTH; t++){

			if (ITEMPOSITION == m_buffer[i][t]){

				//��芸����
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
//�I�����ꂽ�R�[�X�Ƀ`�F�b�N�|�C���g��z�u����
//�`�F�b�N�|�C���g�̍��W�͊O���e�L�X�g�t�@�C���ɕۊ�

void Course::SetCheckPoint(const char *_txtName) 
{

	FILE *fp = fopen(_txtName, "r");
	assert(fp != nullptr);

	for (int i = 0; i < Course::checkPointNum; i++)
	{
		oka::Vec3 position;
		fscanf(fp, "(%f,%f,%f)", &position.m_x, &position.m_y, &position.m_z);
		fscanf(fp, "%*c"); //���s�����ǂݔ�΂�

		m_checkPoint[i].m_position = position;

	}

}

//-------------------------------------
//�I�����ꂽ�R�[�X��AI����p�̃|�C���g��z�u����
//�`�F�b�N�|�C���g�̍��W�͊O���e�L�X�g�t�@�C���ɕۊ�

void Course::SetAimPoint(const char *_txtName) 
{
	FILE *fp = fopen(_txtName, "r");
	assert(fp != nullptr);

	for (int i = 0; i < Course::aimPointNum; i++)
	{
		oka::Vec3 position;
		fscanf(fp, "(%f,%f,%f)", &position.m_x, &position.m_y, &position.m_z);
		fscanf(fp, "%*c"); //���s�����ǂݔ�΂�

		m_aimPoint[i].m_position = position;

	}

}
