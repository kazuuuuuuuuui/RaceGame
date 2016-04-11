#ifndef COURSE_H_
#define COURSE_H_

//必ず使用するテクスチャの縦横とサイズを合わせること
#define COURSE_WIDTH (256)
#define COURSE_HEIGHT (256)

//コースに配置されている魔石の数
#define SET_ITEM_NUMBER (20)

#include<stdlib.h>
#include<vector>
#include"Item.h"
#include"BmpImage.h"
#include"CheckPoint.h"
#include"GameObject.h"
#include"AimPoint.h"
#include"Sound.h"
#include"Vec3.h"
#include"glut.h"

//-------------------------------------
//コースの各ピクセルの情報

enum 
{
	PATH = 0,
	DART,
	START,
	GOAL,
	ITEMPOSITION
};


//-------------------------------------
//コースの情報

class Course :public oka::GameObject 
{
public:

	const char *m_name;

	//コースに設置してある
	//周回判定用のチェックポイントの個数
	static const int checkPointNum = 10;

	//コースに設置してある
	//敵キャラAI用のポイントの個数
	static const int aimPointNum = 25;

	//頂点数
	unsigned int m_vertices;

	//インデックス数
	unsigned int m_indeces;

	//頂点情報
	std::vector<oka::Vec3>m_vertex;

	//インデックス情報
	std::vector<unsigned short>m_index;

	//法線情報
	std::vector<oka::Vec3>m_normal;

	//uv情報
	std::vector<glm::vec2>m_tex;

	int m_width;
	int m_height;

	int m_depth;

	int m_buffer[COURSE_HEIGHT][COURSE_WIDTH];   //各コースの各ピクセルの情報を格納するバッファ
	
	unsigned int m_handle;							 //コースのテクスチャ
	unsigned int m_bgm;
	
	CheckPoint m_checkPoint[checkPointNum]; //周回判定用のポイント
	AimPoint m_aimPoint[aimPointNum];			 //敵AI用のポイント
	
	static const oka::Vec3 m_backgroundColor;

	void Draw();
	void Update() {};

	void SetVertex();
	void SetIndex();
	void SetNormal();
	void SetTex();
	void SetHeight(const char *_fileName);
	
	void MakeBuffer(const char *_fileName);

	void SetItem();
	void SetCheckPoint(const char *_txtName);
	void SetAimPoint(const char *_txtName);

	Course();
	~Course();

};

#endif

