#include"ImageManager.h"
#include"glut.h"

namespace oka
{

	ImageManager* ImageManager::m_instance = nullptr;

	//-------------------------------------
	//ƒVƒ“ƒOƒ‹ƒgƒ“‚É‚·‚é‚½‚ßƒCƒ“ƒXƒ^ƒ“ƒX‚ª‚È‚¢ê‡‚Ì‚Ýnew‚µ
	//Šù‚ÉƒCƒ“ƒXƒ^ƒ“ƒX‚ª‚ ‚éê‡‚Í‚»‚ÌƒCƒ“ƒXƒ^ƒ“ƒX‚ð‚»‚Ì‚Ü‚Ü•Ô‚·

	ImageManager* ImageManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new ImageManager();
		}

		return m_instance;
	}

	//-------------------------------------
	//ˆø”‚Æ‚µ‚ÄŽó‚¯Žæ‚Á‚½ƒeƒNƒXƒ`ƒƒƒnƒ“ƒhƒ‹‚ð
	//ŠÇ—‚µ‚Ä‚¢‚émap‚ÉŠù‚É“o˜^‚³‚ê‚Ä‚¢‚é‚©ŒŸõ‚µ
	//“o˜^‚³‚ê‚Ä‚¢‚È‚¯‚ê‚Î“o˜^‚·‚é

	void ImageManager::SetHandle(const std::string _str, const unsigned int _handle)
	{
		if (m_images.find(_str) == m_images.end())
		{
			m_images.insert(std::make_pair(_str, _handle));
		}
		else
		{
			printf("%s‚ÍŠù‚É“o˜^‚³‚ê‚Ä‚¢‚Ü‚·\n", _str);
		}
	}

	//-------------------------------------
	//ˆø”‚Æ‚µ‚ÄŽó‚¯Žæ‚Á‚½key‚ªmap‚É“o˜^‚³‚ê‚Ä‚¢‚é‚©
	//ŒŸõ‚µ“o˜^‚³‚ê‚Ä‚¢‚ê‚ÎƒeƒNƒXƒ`ƒƒ‚ðíœ‚µ
	//map‚©‚çœŠO‚·‚é

	void ImageManager::DeleteHandle(const std::string _str)
	{
		glDeleteTextures(1, &m_images.find(_str)->second);
		m_images.erase(_str);
	}


	//-------------------------------------
	//ˆø”‚Æ‚µ‚ÄŽó‚¯Žæ‚Á‚½key‚ªmap‚É“o˜^‚³‚ê‚Ä‚¢‚é‚©
	//ŒŸõ‚µ“o˜^‚³‚ê‚Ä‚¢‚ê‚Î‚»‚Ìkey‚É‘Î‰ž‚·‚éƒeƒNƒXƒ`ƒƒƒnƒ“ƒhƒ‹‚ð•Ô‚·

	unsigned int ImageManager::GetHandle(const std::string _str)const
	{
		if (m_images.find(_str) == m_images.end())
		{
			//—vC³
			return 0;
		}
		else
		{
			return m_images.find(_str)->second;
		}
	}


}//namespace oka