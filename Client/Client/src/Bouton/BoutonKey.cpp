#include <Bouton/BoutonKey.h>

BoutonKey::BoutonKey(sf::Vector2f pos, sf::Vector2f posTxt, std::string str_txtr, std::string txt_def, short txt_max_size, short cara_size, sf::Color color) : Bouton(pos, str_txtr, 0) {
	this->initTexte(posTxt, txt_def, cara_size, color);
	m_max_size = txt_max_size;
	m_key = true;
	m_txt_ent = false;
}

BoutonKey::BoutonKey(sf::Sprite spr, sf::Vector2f posTxt, std::string txt_def, short txt_max_size, short cara_size, sf::Color color) : Bouton(spr, 0) {
	this->initTexte(posTxt, txt_def, cara_size, color);
	m_max_size = txt_max_size;
	m_key = true;
	m_txt_ent = false;
}

BoutonKey::~BoutonKey() {}

short BoutonKey::verifIB(sf::Vector2f posC) {
	if (m_itBox.contains(posC)) {
		m_txt_ent = !m_txt_ent;
	} else {
		m_txt_ent = false;
	}
	return m_adrs;
}

void BoutonKey::setPosTxt(sf::Vector2f posTxt) {
	m_text_aff.setPosition(posTxt + m_sprite.getPosition());
}

void BoutonKey::setDefaultText(std::string txt_def) {
	m_text_def = txt_def;
	m_text_aff.setString(m_text_def);
}

void BoutonKey::setMaxSize(short txt_max_size) {
	m_max_size = txt_max_size;
}

void BoutonKey::setCaraSize(short cara_size) {
	m_text_aff.setCharacterSize(cara_size);
}

void BoutonKey::setColor(sf::Color color) {
	m_text_aff.setFillColor(color);
}

void BoutonKey::initTexte(sf::Vector2f posTxt, std::string txt_def, short cara_size, sf::Color color) {
	if (!m_font.loadFromFile("bin/font/Roboto-Regular.ttf")) {
		std::cout << "Erreur lors du chargement de la police decriture" << std::endl;
	}
	m_text_aff.setFont(m_font);
	m_text_def = txt_def;
	m_text_aff.setString(m_text_def);
	m_text_aff.setCharacterSize(cara_size);
	m_text_aff.setFillColor(color);
	m_text_aff.setPosition(posTxt + m_sprite.getPosition());
}

void BoutonKey::updateTxt() {
	if ((m_txt_ent) || (m_text_act.size() > 1)) {
		m_text_aff.setString(m_text_act);
	}
	else {
		m_text_aff.setString(m_text_def);
	}
}

void BoutonKey::entKey(sf::Uint32 key) {
	if (m_txt_ent) {
		if (m_text_act.size() < m_max_size) {
			if ((key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key == 95) || (key == 32)) {
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

std::string BoutonKey::getEntry() { return m_text_act; }

void BoutonKey::draw(sf::RenderWindow& screen) {
	screen.draw(m_sprite);
	this->updateTxt();
	screen.draw(m_text_aff);
}