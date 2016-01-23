#ifndef XFILE_H_
#define XFILE_H_

#include<vector>

class xFile{
public:
	//���_��
	unsigned int m_vertices;

	//�C���f�b�N�X��
	unsigned int m_indeces;

	//���_���
	std::vector<float>m_vertex;

	//�C���f�b�N�X���
	std::vector<unsigned short>m_index;

	//�@�����
	std::vector<float>m_normal;

	static void loadXfile(const char *_xFileName,xFile &_model);
};

#endif