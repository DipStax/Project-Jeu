#include <SFML/Network.hpp>
#include <iostream>
#include <Reseau/clientToServ.h>
#include <Personnage/perso.h>

#define SOCLIENT 40000

namespace stc {
	std::string tryCo(sf::TcpSocket& servReceive, sf::TcpSocket& servSend, sf::TcpListener& listener);
	std::string getIP(sf::TcpSocket& socketServ);
	int AccGen(std::vector<std::unique_ptr<Perso>>& listPerso, sf::Packet& packet, std::string& dirError);
	void receiveMaxStuff(std::unique_ptr<Perso>& perso, sf::TcpSocket& servReceive, sf::TcpListener& listener);
}