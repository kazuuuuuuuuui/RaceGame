#include"ImageManager.h"
#include"glut.h"

namespace oka
{

	ImageManager* ImageManager::m_instance = nullptr;

	//-------------------------------------
	//シングルトンにするためインスタンスがない場合のみnewし
	//既にインスタンスがある場合はそのインスタンスをそのまま返す

	ImageManager* ImageManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new ImageManager();
		}

		return m_instance;
	}

	//-------------------------------------
	//引数として受け取ったテクスチャハンドルを
	//管理しているmapに既に登録されているか検索し
	//登録されていなければ登録する

	void ImageManager::SetHandle(const std::string _str, const unsigned int _handle)
	{
		if (m_images.find(_str) == m_images.end())
		{
			m_images.insert(std::make_pair(_str, _handle));
		}
		else
		{
			
		}
	}

	//-------------------------------------
	//引数として受け取ったkeyがmapに登録されているか
	//検索し登録されていればテクスチャを削除し
	//mapから除外する

	void ImageManager::DeleteHandle(const std::string _str)
	{
		glDeleteTextures(1, &m_images.find(_str)->second);
		m_images.erase(_str);
	}


	//-------------------------------------
	//引数として受け取ったkeyがmapに登録されているか
	//検索し登録されていればそのkeyに対応するテクスチャハンドルを返す

	unsigned int ImageManager::GetHandle(const std::string _str)const
	{
		if (m_images.find(_str) == m_images.end())
		{
			//要修正
			return 0;
		}
		else
		{
			return m_images.find(_str)->second;
		}
	}


}//namespace oka