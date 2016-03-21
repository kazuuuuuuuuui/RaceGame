#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<windows.h>
#include<assert.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtx\transform.hpp"
#include"glm\glm.hpp"
#include"xFile.h"

//-------------------------------------
//x�t�@�C������3D���f����ǂݍ���
//�@�������͌v�Z(�t���b�g�V�F�C�f�B���O)����
//������x�t�@�C�����ƃ��f���f�[�^���i�[����o�b�t�@��n��

void xFile::loadXfile(const char *_xFileName, xFile &_model)
{

	FILE *pFile = fopen(_xFileName, "r");

	assert(pFile != NULL);

	char buf[256];
	char prevBuf[256];
	while (EOF != fscanf(pFile, "%s", buf)){
		if (strcmp("Mesh", buf) == 0 && 0 != strcmp("template", prevBuf) && 0 != strcmp("the", prevBuf)){

			fscanf(pFile, "%s", buf);

			//���_���ǂݍ���
			fscanf(pFile, "%u", &(_model.m_indeces));

			fscanf(pFile, "%*c", buf);

			//���_�̓ǂݍ���
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

				//�@���v�Z
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

			//�C���f�b�N�X���ǂݍ���
			fscanf(pFile, "%u", &(_model.m_indeces));

			fscanf(pFile, "%*c", buf);//*�͓ǂݎ̂Ă�

			//�C���f�b�N�X�̓ǂݍ���
			for (unsigned int i = 0; i < _model.m_indeces; i++){

				fscanf(pFile, "%*2s", buf);//*�͓ǂݎ̂Ă�

				unsigned short indeces[3];
				fscanf(pFile, "%hu", &indeces[0]);

				fscanf(pFile, "%*c", buf);//*�͓ǂݎ̂Ă�

				fscanf(pFile, "%hu", &indeces[1]);

				fscanf(pFile, "%*c", buf);//*�͓ǂݎ̂Ă�

				fscanf(pFile, "%hu", &indeces[2]);

				fscanf(pFile, "%*s", buf);//*�͓ǂݎ̂Ă�

				_model.m_index.push_back(indeces[0]);
				_model.m_index.push_back(indeces[1]);
				_model.m_index.push_back(indeces[2]);
			}

		}

		strcpy(prevBuf, buf);
	}


	fclose(pFile);
}


//�ԑ̂̌��������̂��߂̊֐�
void xFile::rotate(){

	//���_�̏C��
	for (int i = 0; i < m_vertex.size(); i += 3){

		glm::vec4 v(m_vertex[i], m_vertex[i + 1], m_vertex[i + 2], 0.0f);


		v = glm::rotate(-90.0f * (float)(M_PI / 180.0f), glm::vec3(1, 0, 0)) * v;
		v = glm::rotate(180.0f * (float)(M_PI / 180.0f), glm::vec3(0, 1, 0)) * v;

		m_vertex[i + 0] = v.x;
		m_vertex[i + 1] = v.y;
		m_vertex[i + 2] = v.z;

	}

	//�@���̏C��
	for (int i = 0; i < m_normal.size(); i += 3){

		glm::vec4 v(m_normal[i], m_normal[i + 1], m_normal[i + 2], 0.0f);


		v = glm::rotate(-90.0f * (float)(M_PI / 180.0f), glm::vec3(1, 0, 0)) * v;
		v = glm::rotate(180.0f * (float)(M_PI / 180.0f), glm::vec3(0, 1, 0)) * v;


		m_normal[i + 0] = v.x;
		m_normal[i + 1] = v.y;
		m_normal[i + 2] = v.z;

	}

}