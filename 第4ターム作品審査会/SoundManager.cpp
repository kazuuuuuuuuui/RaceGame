#include"SoundManager.h"

SoundManager* SoundManager::m_instance = nullptr;

//-------------------------------------------------------------------------------------------------------
SoundManager* SoundManager::getInstance() {

	if (nullptr == m_instance) {
		m_instance = new SoundManager();
	}
	return m_instance;
}


//-------------------------------------------------------------------------------------------------------
void SoundManager::updata() {


}

//-------------------------------------
//������key��Sound�^��value���󂯎����
//�����o��map�Ɋ��ɓo�^����Ă��邩�`�F�b�N���Ă���ǉ�����

void SoundManager::addSound(const std::string _str,Sound *_sound) {

	//auto itr = m_sounds.find(_str);
	//if (itr!=m_sounds.end()) {

		m_sounds[_str] = _sound;

	//}

}