#ifndef DEF_STUFF
#define DEF_STUFF

#include <SFML/Graphics.hpp>
#include <iostream>

#include <Serv_Personnage/Stat.h>

#include <Serv_Item/item.h>
#include <Serv_Item/enchant.h>
#include <iomanip>

class stuff : public item {
public:
	stuff();
	stuff(int ID, std::string name, short maxSlot, PIECE piece, int lvlMin);
	stuff(int ID, std::string name, short maxSlot, PIECE piece, int lvlMin, statistic& stat);
	~stuff();

	int getNbEnchant() const;
	std::vector<enchant>& getEnchant();
	short getMaxSlot() const;
	statistic& getStat();
	int getMinLvl() const;
	void getAllStat(std::vector<int>& stat);
	void getStat(std::vector<int>& stat);
	PIECE getPiece();

	void addStat(statistic& stat);
	bool addEnchant(enchant& enchant_);

	void inPacket(sf::Packet& packet);
	friend sf::Packet& operator<<(sf::Packet& packet, stuff& stuff_);
	friend sf::Packet& operator>>(sf::Packet& packet, stuff& stuff_);
	friend std::ostream& operator<<(std::ostream &os, stuff& stuff_);
private:
	void write();
	void getEnchantStat(std::vector<int>& stat);
	PIECE m_piece;
	short m_maxSlot, m_nbEnchant;
	statistic m_stat;
	std::vector<enchant> m_enchant;
	int m_lvlMin;
};

#endif