#include <Item/stuff.h>

stuff::stuff() : item(0, "none", TypeObj::STUFF) {}

stuff::stuff(int ID, std::string name, short maxSlot, PIECE piece, int lvlMin) : item(ID, name, TypeObj::STUFF) {
	m_maxSlot = maxSlot;
	m_piece = piece;
	m_lvlMin = lvlMin;
	this->initSprite();
}

stuff::stuff(int ID, std::string name, short maxSlot, PIECE piece, int lvlMin, statistic& stat) : stuff(ID, name, maxSlot, piece, lvlMin) {
	m_stat = stat;
}

stuff::~stuff() {}

int stuff::getNbEnchant() const { return m_enchant.size(); }
std::vector<enchant>& stuff::getEnchant() { return m_enchant; }
short stuff::getMaxSlot() const { return m_maxSlot; }
statistic& stuff::getStat() { return m_stat; }
int stuff::getMinLvl() const { return m_lvlMin; }

void stuff::addStat(statistic& stat) {
	m_stat = stat;
}

bool stuff::addEnchant(enchant& enchant_) {
	if (m_enchant.size() < m_maxSlot) {
		m_enchant.push_back(enchant_);
		return true;
	}
	return false;
}

void stuff::getAllStat(std::vector<int>& stat) {
	stat.clear();
	this->getEnchantStat(stat);
	m_stat.getStat(stat);
}

void stuff::getStat(std::vector<int>& stat) {
	m_stat.getStat(stat);
}

void stuff::getEnchantStat(std::vector<int>& stat) {
	stat.clear();
	std::vector<int> stat_e;
	for (auto&& a : m_enchant) {
		a.getStat(stat_e);
	}
}

PIECE stuff::getPiece() { return m_piece; }

void stuff::rdTxtrDraw(sf::RenderTexture& rdTxtr) {
	rdTxtr.draw(m_sprite);
	// render a white rect w/o the stuff
}

void stuff::inPacket(sf::Packet& packet) {
	packet << (sf::Uint32)m_ID << m_name << static_cast<sf::Uint8>(m_typeObj) << (sf::Uint8)m_maxSlot << static_cast<sf::Uint8>(m_piece) << (sf::Uint8)m_lvlMin
		   << m_stat << (sf::Uint8)m_enchant.size();
	for (auto& enchant_ : m_enchant) {
		packet << enchant_;
	}
}

sf::Packet& operator<<(sf::Packet& packet, stuff& stuff_) {
	std::cout << "<---------->" << std::endl << "Packet << Stuff" << std::endl;
	std::cout << stuff_.getID() << std::endl;
	packet << (sf::Uint32)stuff_.getID() << stuff_.getName() << static_cast<sf::Uint8>(stuff_.getTypeObj()) << (sf::Uint8)stuff_.getMaxSlot()
		<< static_cast<sf::Uint8>(stuff_.getPiece()) << (sf::Uint8)stuff_.getMinLvl() << stuff_.getStat() << (sf::Uint8)stuff_.getNbEnchant();
	for (auto& enchant_ : stuff_.getEnchant()) {
		packet << enchant_;
	}
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, stuff& stuff_) {
	statistic stat;
	std::string name;
	sf::Uint8 nbEnchant, typeObj, maxSlot, piece, minLvl;
	sf::Uint32 ID;
	packet >> ID >> name >> typeObj >> maxSlot >> piece >> minLvl >> stat;
	if (!(packet >> nbEnchant))
		std::cout << "Fail" << std::endl;
		
	std::cout << "NbEnchant: " << nbEnchant << std::endl;
	stuff stuff__(ID, name, maxSlot, static_cast<PIECE>(piece), minLvl, stat);
	packet >> nbEnchant;
	for (int i = 0; i < nbEnchant; i++) {
		packet >> ID >> name >> typeObj;
		enchant enchant_(ID, name);
		packet >> enchant_;
		stuff__.addEnchant(enchant_);
	}
	stuff_ = stuff__;
	return packet;
}

std::ostream& operator<<(std::ostream& os, stuff& stuff_) {
	stuff_.write();
	return os;
}

void stuff::write() {
	std::cout << "Type d'object: " << static_cast<int>(m_typeObj) << std::endl;
	std::cout << "Piece: " << static_cast<int>(m_piece) << std::endl;
	std::cout << "ID: " << m_ID << std::endl;
	std::cout << "Name: " << m_name << std::endl;
	std::cout << "Stat:" << m_stat;
}

void stuff::initSprite() {
	std::string path = "./bin/img/stuff/";
	switch (m_piece) {
	case PIED: 
		path += "Pied/";
		break;
	case JAMBE: 
		path += "Jambe/";
		break;
	case TORSE: 
		path += "Torse/";
		break;
	case MAIN: 
		path += "Main/";
		break;
	case TETE: 
		path += "Tete/";
		break;
	case ARME: 
		path += "Arme/";
		break;
	case ARMESEC:
		path += "Arme/";
		break;
	}
	path += m_name + ".png";
	if (!m_txtr.loadFromFile(path)) {
		std::cout << "Error loading texture: " << path << std::endl;
		return;
	}
	m_sprite.setTexture(m_txtr);
	std::cout << "The texture: " << path << " as loaded succesfuly" << std::endl;
}