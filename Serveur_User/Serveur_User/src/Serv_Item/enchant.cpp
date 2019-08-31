#include <Serv_Item/enchant.h>

enchant::enchant() {}

enchant::enchant(int ID, std::string name) : item(ID, name, TypeObj::ENCH) {}

enchant::enchant(int ID, std::string name, statistic& stat) : item(ID, name, TypeObj::ENCH) {
	m_stat = stat;
}

enchant::~enchant() {}

statistic& enchant::getStat() { return m_stat; }

void enchant::addStat(statistic& stat) {
	m_stat = stat;
}

void enchant::getStat(std::vector<int>& stat) {
	stat.clear();
	m_stat.getStat(stat);
}

void enchant::inPacket(sf::Packet& packet) {
	packet << (sf::Uint32)m_ID << m_name << (sf::Uint8)m_typeObj << m_stat;
}

void enchant::inJson(nlohmann::json& json) {
	json["ID"] = m_ID;
	json["TypeObj"] = m_typeObj;
	json["Name"] = m_name;
}

sf::Packet& operator<<(sf::Packet& packet, enchant& enchant_) {
	packet << (sf::Uint32)enchant_.getID() << enchant_.getName() << static_cast<sf::Uint8>(enchant_.getTypeObj()) << enchant_.getStat();
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, enchant& enchant_) {
	statistic stat;
	packet >> stat;
	enchant_.addStat(stat);
	return packet;
}

std::ostream& operator<<(std::ostream &os, enchant& enchant_) {
	enchant_.write();
	return os;
}

nlohmann::json& operator<<(nlohmann::json& json, enchant& enchant_) {
	json["ID"] = enchant_.getID();
	json["TypeObj"] = enchant_.getTypeObj();
	json["Name"] = enchant_.getName();
	return json;
}

void enchant::write() {
	std::cout << "Type d'object: " << static_cast<int>(m_typeObj) << std::endl;
	std::cout << "ID: " << m_ID << std::endl;
	std::cout << "Name: " << m_name << std::endl;
	std::cout << "Stat: " << m_stat;
}