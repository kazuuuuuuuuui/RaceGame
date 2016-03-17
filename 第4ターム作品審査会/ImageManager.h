#ifndef _OKA_IMAGEMANAGER_H_
#define _OKA_IMAGEMANAGER_H_

#include<map>
#include<string>

namespace oka
{

	//-------------------------------------
	//ゲーム中で使用するテクスチャを管理するクラス

	class ImageManager
	{
	private:
		static ImageManager* m_instance;
		std::map<std::string, unsigned int>m_images;

	public:
		static ImageManager* GetInstance();
		void SetHandle(const std::string _str, const unsigned int _handle);
		void DeleteHandle(const std::string _str);
		unsigned int GetHandle(const std::string _str)const;
	};

}

#endif
