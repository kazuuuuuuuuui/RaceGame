#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<windows.h>
#include<assert.h>
#include"Player.h"
#include"glm\glm.hpp"
#include"xFile.h"

//-------------------------------------
//x�t�@�C������3D���f����ǂݍ���
//�@�������͌v�Z(�O�[���[�V�F�C�f�B���O)����


/*���������r���I�I�I*/

void xFile::loadXfile(const char *_xFileName, const unsigned int &_vertices){
	
	FILE *pFile = fopen(_xFileName, "r");
	
	assert(pFile != NULL);

	char buf[256];
	char prevBuf[256];
	while (EOF != fscanf(pFile, "%s", buf)){
		if (strcmp("Mesh", buf) == 0 && 0 != strcmp("template", prevBuf) && 0 != strcmp("the", prevBuf)){
			//printf("%s\n", buf);//Mesh

			fscanf(pFile, "%s", buf);

			//���_���ǂݍ���
			fscanf(pFile, "%u", &_vertices);
			//printf("nVertices:%u\n", nVertices);

			fscanf(pFile, "%s", buf);
			//printf("%s\n", buf);

			//���_�̓ǂݍ���
			for (int i = 0; i < _vertices / 3; i++){
				glm::vec3 v[3];
				glm::vec3 n;

				fscanf(pFile, "%f", &v[0].x);
				fscanf(pFile, "%*c", buf);

				fscanf(pFile, "%f", &v[0].y);
				fscanf(pFile, "%*c", buf);

				fscanf(pFile, "%f", &v[0].z);
				fscanf(pFile, "%*s", buf);

				player->m_vertex.push_back(v[0].x);
				player->m_vertex.push_back(v[0].y);
				player->m_vertex.push_back(v[0].z);

				fscanf(pFile, "%f", &v[1].x);
				fscanf(pFile, "%*c", buf);

				fscanf(pFile, "%f", &v[1].y);
				fscanf(pFile, "%*c", buf);

				fscanf(pFile, "%f", &v[1].z);
				fscanf(pFile, "%*s", buf);

				player->m_vertex.push_back(v[1].x);
				player->m_vertex.push_back(v[1].y);
				player->m_vertex.push_back(v[1].z);

				fscanf(pFile, "%f", &v[2].x);
				fscanf(pFile, "%*c", buf);

				fscanf(pFile, "%f", &v[2].y);
				fscanf(pFile, "%*c", buf);

				fscanf(pFile, "%f", &v[2].z);
				fscanf(pFile, "%*s", buf);

				player->m_vertex.push_back(v[2].x);
				player->m_vertex.push_back(v[2].y);
				player->m_vertex.push_back(v[2].z);

				//�@���v�Z
				glm::vec3 v01 = v[1] - v[0];
				glm::vec3 v02 = v[2] - v[0];

				n = glm::cross(v01, v02);

				player->m_normal.push_back(n.x);
				player->m_normal.push_back(n.y);
				player->m_normal.push_back(n.z);

				player->m_normal.push_back(n.x);
				player->m_normal.push_back(n.y);
				player->m_normal.push_back(n.z);

				player->m_normal.push_back(n.x);
				player->m_normal.push_back(n.y);
				player->m_normal.push_back(n.z);
			}

			//�C���f�b�N�X���ǂݍ���
			fscanf(pFile, "%u", &player->m_indeces);
			//printf("nIndeces:%u\n", player->m_indeces);

			fscanf(pFile, "%*c", buf);//*�͓ǂݎ̂Ă�

			//�C���f�b�N�X�̓ǂݍ���
			for (int i = 0; i < player->m_indeces; i++){
				fscanf(pFile, "%*2s", buf);//*�͓ǂݎ̂Ă�
				unsigned short indeces[3];
				fscanf(pFile, "%hu", &indeces[0]);
				//printf("%hu\n", indeces[0]);

				fscanf(pFile, "%*c", buf);//*�͓ǂݎ̂Ă�

				fscanf(pFile, "%hu", &indeces[1]);
				//printf("%hu\n", indeces[1]);

				fscanf(pFile, "%*c", buf);//*�͓ǂݎ̂Ă�

				fscanf(pFile, "%hu", &indeces[2]);
				//printf("%hu\n", indeces[2]);
				fscanf(pFile, "%*s", buf);//*�͓ǂݎ̂Ă�

				player->m_index.push_back(indeces[0]);
				player->m_index.push_back(indeces[1]);
				player->m_index.push_back(indeces[2]);
			}

		}

		strcpy(prevBuf, buf);
	}
	

	fclose(pFile);
}