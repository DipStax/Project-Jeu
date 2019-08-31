#ifndef DEF_ENCHANT
#define DEF_ENCHANT

#include <SFML/Graphics.hpp>

#include <iostream>

#include <Serv_Personnage/Stat.h>
#include <Serv_Item/item.h>

class enchant : public item {
public:
	enchant();
	enchant(int ID, std::string name);
	enchant(int ID, std::string name, statistic& stat);
	~enchant();

	statistic& getStat();

	void addStat(statistic& stat);
	void getStat(std::vector<int>& stat);

	void inPacket(sf::Packet& packet);
	void inJson(nlohmann::json& json);
	friend sf::Packet& operator<<(sf::Packet& packet, enchant& enchant_);
	friend sf::Packet& operator<<(sf::Packet& packet, enchant& enchant_);
	friend std::ostream& operator<<(std::ostream &os, enchant& enchant_);
	friend nlohmann::json& operator<<(nlohmann::json& json, enchant& enchant_);
private:
	void write();
	statistic m_stat;
};

#endif