#pragma once
#include <SFML/Network.hpp>
#include <Gestion/PersoJson.h>
#include <sstream>

class SplitPointDot : public std::string {};
class SplitSlash : public std::string {};

std::istream& operator>>(std::istream& is, SplitPointDot& output);
std::istream& operator>>(std::istream& is, SplitSlash& output);

namespace gpg {
	void addMinStuff(std::unique_ptr<Perso>& perso, std::string adrsIP);
	void savePerso(std::unique_ptr<Perso>& perso, int IDcompte, sqlite3* db);

	void sendMaxStuff(sf::Packet& packet);

	std::vector<stuff> genStuffMin(int type);
	std::vector<stuff> genStuffMax(int type);
	std::vector<std::vector<std::string>> genWord(std::string path);
	stuff genStuffLine(std::vector<std::string> line);

}