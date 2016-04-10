#include"ImageManager.h"
#include"glut.h"

namespace oka
{

	ImageManager* ImageManager::m_instance = nullptr;

	//-------------------------------------
	//�V���O���g���ɂ��邽�߃C���X�^���X���Ȃ��ꍇ�̂�new��
	//���ɃC���X�^���X������ꍇ�͂��̃C���X�^���X�����̂܂ܕԂ�

	ImageManager* ImageManager::GetInstance()
	{
		if (nullptr == m_instance)
		{
			m_instance = new ImageManager();
		}

		return m_instance;
	}

	//-------------------------------------
	//�����Ƃ��Ď󂯎�����e�N�X�`���n���h����
	//�Ǘ����Ă���map�Ɋ��ɓo�^����Ă��邩������
	//�o�^����Ă��Ȃ���Γo�^����

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
	//�����Ƃ��Ď󂯎����key��map�ɓo�^����Ă��邩
	//�������o�^����Ă���΃e�N�X�`�����폜��
	//map���珜�O����

	void ImageManager::DeleteHandle(const std::string _str)
	{
		glDeleteTextures(1, &m_images.find(_str)->second);
		m_images.erase(_str);
	}


	//-------------------------------------
	//�����Ƃ��Ď󂯎����key��map�ɓo�^����Ă��邩
	//�������o�^����Ă���΂���key�ɑΉ�����e�N�X�`���n���h����Ԃ�

	unsigned int ImageManager::GetHandle(const std::string _str)const
	{
		if (m_images.find(_str) == m_images.end())
		{
			//�v�C��
			return 0;
		}
		else
		{
			return m_images.find(_str)->second;
		}
	}


}//namespace oka