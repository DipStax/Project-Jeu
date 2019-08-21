#include <Bouton/BoutonKeyEmail.h>

BoutonKeyEmail::BoutonKeyEmail(sf::Vector2f pos, sf::Vector2f posTxt, std::string str_txtr, std::string txt_def, short txt_max_size, short cara_size, sf::Color color) :
								BoutonKey(pos, posTxt, str_txtr, txt_def, txt_max_size, cara_size, color) {}

BoutonKeyEmail::BoutonKeyEmail(sf::Sprite spr, sf::Vector2f posTxt, std::string txt_def, short txt_max_size, short cara_size, sf::Color color) :
								BoutonKey(spr, posTxt, txt_def, txt_max_size, cara_size, color) {}

BoutonKeyEmail::~BoutonKeyEmail() {};

void BoutonKeyEmail::entKey(sf::Uint32 key) {
	if (m_txt_ent) {
		if (m_text_act.size() < m_max_size) {
			if ((key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key == 95) || (key == 64) || (key == 46)) {
				char char_tmp = static_cast<char>(key);
				m_text_act += char_tmp;
			}
		}
		if (m_text_act.size() > 0) {
			if (key == 8) {
				m_text_act.pop_back();
			}
		}
		if (key == 13) {
			m_txt_ent = false;
		}
		this->updateTxt();
	}
}