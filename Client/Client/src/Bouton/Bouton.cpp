#include <Bouton/Bouton.h>

Bouton::Bouton() {}

Bouton::Bouton(sf::Vector2f pos, std::string str_txtr, short adrs) {
	this->initTexture(str_txtr, pos);
	m_adrs = adrs;
}

Bouton::Bouton(sf::Sprite spr, short adrs) {
	m_sprite = spr;
	m_adrs = adrs;
	m_itBox = m_sprite.getGlobalBounds();
}

Bouton::~Bouton() {}

short Bouton::verif_event(sf::Event event, sf::Vector2f posC) {
	if (event.type == sf::Event::MouseButtonReleased) {
		auto adrs_tmp = this->verifIB(posC);
		return adrs_tmp;
	}
	else if (event.type == sf::Event::TextEntered) {
		if (this->isKey()) {
			this->entKey(event.text.unicode);
		}
	}
	return 0;
}

void Bouton::setPos(sf::Vector2f pos) {
	m_sprite.setPosition(pos);
}

void Bouton::setTxtr(std::string str_txtr) {
	if (!m_texture.loadFromFile(str_txtr)) {
		std::cout << "Erreur de chargement d'une l'image, lors de sa modification" << std::endl;
	}
}

void Bouton::setAdrs(short adrs) { 
	m_adrs = adrs; 
}

bool Bouton::isKey() { return m_key; }

void Bouton::initTexture(std::string str_txtr, sf::Vector2f pos) {
	if (!m_texture.loadFromFile(str_txtr)) {
		std::cout << "Erreur de chargement d'une l'image" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(pos);
	m_itBox = m_sprite.getGlobalBounds();
}

short Bouton::verifIB(sf::Vector2f posC) {
	if (m_itBox.contains(posC)) {
		return m_adrs;
	}
	else {
		return 0;
	}
}

void Bouton::entKey(sf::Uint32 key) {}

std::string Bouton::getEntry() { return ""; }

void Bouton::draw(sf::RenderWindow& screen) {
	screen.draw(m_sprite);
}