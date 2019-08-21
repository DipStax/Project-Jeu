#include <Serv_Item/stuff.h>

stuff::stuff() : item(0, "none", TypeObj::STUFF) {
	m_nbEnchant = 0;
}

stuff::stuff(int ID, std::string name, short maxSlot, PIECE piece, int lvlMin) : item(ID, name, TypeObj::STUFF) {
	m_maxSlot = maxSlot;
	m_piece = piece;
	m_nbEnchant = 0;
	m_lvlMin = lvlMin;
}

stuff::stuff(int ID, std::string name, short maxSlot, PIECE piece, int lvlMin, statistic& stat) : stuff(ID, name, maxSlot, piece, lvlMin) {
	m_stat = stat;
}

stuff::~stuff() {}

int stuff::getNbEnchant() const { return m_nbEnchant; }
std::vector<enchant>& stuff::getEnchant() { return m_enchant; }
short stuff::getMaxSlot() const { return m_maxSlot; }
statistic& stuff::getStat() { return m_stat; }
int stuff::getMinLvl() const { return m_lvlMin; }

void stuff::addStat(statistic& stat) {
	m_stat = stat;
}

bool stuff::addEnchant(enchant& enchant_) {
	if (m_nbEnchant < m_maxSlot) {
		m_enchant.push_back(enchant_);
		m_nbEnchant++;
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

void stuff::inPacket(sf::Packet& packet) {
	packet << m_ID << m_name << static_cast<int>(m_typeObj) << m_maxSlot << static_cast<int>(m_piece) << m_lvlMin 
		   << m_stat << m_nbEnchant;
	for (auto& enchant_ : m_enchant) {
		packet << enchant_;
	}
}

sf::Packet& operator<<(sf::Packet& packet, stuff& stuff_) {
	std::cout << "<---------->" << std::endl << "Packet << Stuff" << std::endl;
	std::cout << stuff_.getID() << std::endl;
	packet << stuff_.getID() << stuff_.getName() << static_cast<int>(stuff_.getTypeObj()) << stuff_.getMaxSlot()
		   << static_cast<int>(stuff_.getPiece()) << stuff_.getMinLvl() << stuff_.getStat() << stuff_.getNbEnchant();
	std::cout << stuff_.getPiece() << " : " << static_cast<PIECE>(stuff_.getPiece()) << std::endl;
	for (auto& enchant_ : stuff_.getEnchant()) {
		packet << enchant_;
	}
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, stuff& stuff_) {
	statistic stat;
	std::string name;
	int nbEnchant, ID, typeObj, maxSlot, piece, minLvl;
	packet >> ID >> name >> typeObj >> maxSlot;
	if (packet >> piece) {
		std::cout << "good" << std::endl;
	} 
	packet >> minLvl >> stat >> nbEnchant;
	std::cout << ID << " : " << name << " : " << typeObj << " : " << maxSlot << " : " << piece 
			  << " : " << minLvl << " : " << stat << " : " << nbEnchant << std::endl;
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