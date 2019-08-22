#include <Personnage/Stat.h>

statistic::statistic() {
	for (int i = 0; i < m_nbStat; i++) {
		m_stat.insert(std::pair<short, int>(i, 0));
	}
}

void statistic::setStat(int stat, ValType value) {
	m_stat.at(value) = stat;
}

void statistic::getStat(std::vector<int>& stat) {
	stat.clear();
	for (int i = 0; i < m_nbStat; i++) {
		stat.push_back(m_stat.at(i));
	}
}

sf::Packet& operator<<(sf::Packet& packet, statistic& stat) {
	std::vector<int> vec;
	stat.getStat(vec);
	for (auto& stat_ : vec) {
		packet << stat_;
		std::cout << stat_ << " : " << std::endl;
	}
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, statistic& stat) {
	int stat_;
	ValType val;
	for (int i = 0; i < 9; i++) {
		packet >> stat_;
		val = static_cast<ValType>(i);
		stat.setStat(stat_ / 65536, val);
	}
	return packet;
}

std::ostream& operator<<(std::ostream &os, statistic& stat) {
	stat.write();
	return os;
}

void statistic::write() {
	for (auto& stat : m_stat) {
		std::cout << std::get<1>(stat) << " / ";
	}
	std::cout << std::endl;
}