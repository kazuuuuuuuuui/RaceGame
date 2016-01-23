#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<windows.h>
#include<assert.h>
//#include"Player.h"
#include"glm\glm.hpp"
#include"xFile.h"

//-------------------------------------
//xファイルから3Dモデルを読み込み
//法線を自力計算(グーローシェイディング)する
//引数にxファイル名とモデルデータを格納するバッファを渡す

void xFile::loadXfile(const char *_xFileName, xFile &_model){

	FILE *pFile = fopen(_xFileName, "r");

	assert(pFile != NULL);

	char buf[256];
	char prevBuf[256];
	while (EOF != fscanf(pFile, "%s", buf)){
		if (strcmp("Mesh", buf) == 0 && 0 != strcmp("template", prevBuf) && 0 != strcmp("the", prevBuf)){

			fscanf(pFile, "%s", buf);

			//頂点数読み込み
			fscanf(pFile, "%u", &(_model.m_indeces));

			fscanf(pFile, "%*c", buf);

			//頂点の読み込み
			for (int i = 0; i < _model.m_indeces / 3; i++){
				glm::vec3 v[3];
				glm::vec3 n;

				fscanf(pFile, "%f", &v[0].x);
				fscanf(pFile, "%*c", buf);

				fscanf(pFile, "%f", &v[0].y);
				fscanf(pFile, "%*c", buf);

				fscanf(pFile, "%f", &v[0].z);
				fscanf(pFile, "%*s", buf);

				_model.m_vertex.push_back(v[0].x);
				_model.m_vertex.push_back(v[0].y);
				_model.m_vertex.push_back(v[0].z);

				fscanf(pFile, "%f", &v[1].x);
				fscanf(pFile, "%*c", buf);

				fscanf(pFile, "%f", &v[1].y);
				fscanf(pFile, "%*c", buf);

				fscanf(pFile, "%f", &v[1].z);
				fscanf(pFile, "%*s", buf);

				_model.m_vertex.push_back(v[1].x);
				_model.m_vertex.push_back(v[1].y);
				_model.m_vertex.push_back(v[1].z);

				fscanf(pFile, "%f", &v[2].x);
				fscanf(pFile, "%*c", buf);

				fscanf(pFile, "%f", &v[2].y);
				fscanf(pFile, "%*c", buf);

				fscanf(pFile, "%f", &v[2].z);
				fscanf(pFile, "%*s", buf);

				_model.m_vertex.push_back(v[2].x);
				_model.m_vertex.push_back(v[2].y);
				_model.m_vertex.push_back(v[2].z);

				//法線計算
				glm::vec3 v01 = v[1] - v[0];
				glm::vec3 v02 = v[2] - v[0];

				n = glm::cross(v01, v02);

				_model.m_normal.push_back(n.x);
				_model.m_normal.push_back(n.y);
				_model.m_normal.push_back(n.z);

				_model.m_normal.push_back(n.x);
				_model.m_normal.push_back(n.y);
				_model.m_normal.push_back(n.z);

				_model.m_normal.push_back(n.x);
				_model.m_normal.push_back(n.y);
				_model.m_normal.push_back(n.z);

			}

			//インデックス数読み込み
			fscanf(pFile, "%u", &(_model.m_indeces));

			fscanf(pFile, "%*c", buf);//*は読み捨てる

			//インデックスの読み込み
			for (unsigned int i = 0; i < _model.m_indeces; i++){

				fscanf(pFile, "%*2s", buf);//*は読み捨てる

				unsigned short indeces[3];
				fscanf(pFile, "%hu", &indeces[0]);

				fscanf(pFile, "%*c", buf);//*は読み捨てる

				fscanf(pFile, "%hu", &indeces[1]);

				fscanf(pFile, "%*c", buf);//*は読み捨てる

				fscanf(pFile, "%hu", &indeces[2]);

				fscanf(pFile, "%*s", buf);//*は読み捨てる

				_model.m_index.push_back(indeces[0]);
				_model.m_index.push_back(indeces[1]);
				_model.m_index.push_back(indeces[2]);
			}

		}

		strcpy(prevBuf, buf);
	}


	fclose(pFile);
}