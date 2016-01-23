#ifndef XFILE_H_
#define XFILE_H_

#include<vector>

class xFile{
public:
	//頂点数
	unsigned int m_vertices;

	//インデックス数
	unsigned int m_indeces;

	//頂点情報
	std::vector<float>m_vertex;

	//インデックス情報
	std::vector<unsigned short>m_index;

	//法線情報
	std::vector<float>m_normal;

	static void loadXfile(const char *_xFileName,xFile &_model);
};

#endif