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
//•¶š—ñkey‚ÆSoundŒ^‚Ìvalue‚ğó‚¯æ‚Á‚Ä
//ƒƒ“ƒo‚Ìmap‚ÉŠù‚É“o˜^‚³‚ê‚Ä‚¢‚é‚©ƒ`ƒFƒbƒN‚µ‚Ä‚©‚ç’Ç‰Á‚·‚é

void SoundManager::addSound(const std::string _str,Sound *_sound) {

	//auto itr = m_sounds.find(_str);
	//if (itr!=m_sounds.end()) {

		m_sounds[_str] = _sound;

	//}

}