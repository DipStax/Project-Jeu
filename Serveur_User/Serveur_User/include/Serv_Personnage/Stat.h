#ifndef DEF_STAT
#define DEF_STAT

#include <SFML/Network/Packet.hpp>
#include <iostream>
#include <map>
#include <vector>

enum ValType { MAN, VIE, DMG, ARM, RES, PEA, PEM, SPE, CRI };

class statistic {
public:
	statistic();
	void setStat(int stat, ValType value);
	void getStat(std::vector<int>& stat);

	friend sf::Packet& operator<<(sf::Packet& packet, statistic& stat);
	friend sf::Packet& operator>>(sf::Packet& packet, statistic& stat);
	friend std::ostream& operator<<(std::ostream &os, statistic& stat);

	short m_nbStat = 9;
private:
	void write();
	std::map<short, int> m_stat;
};

#endif