#include <SFML/Network.hpp>
#include <iostream>
#include <Bouton/Bouton.h>
#include <Bouton/BoutonKey.h>
#include <Personnage/perso.h>

#define IPSERV "127.0.0.1"
#define SOSERV 53000
#define SOCLIENT 40000

namespace cts {
	void genIP(sf::TcpSocket& socketServ);
	sf::Packet genPacCo(short adrs, std::vector<std::unique_ptr<Bouton>>& list_btn, std::string adrsIP);
	sf::Packet packetCon(std::vector<std::unique_ptr<Bouton>>& list_btn, std::string adrsIP);
	sf::Packet packetIns(std::vector<std::unique_ptr<Bouton>>& list_btn, std::string adrsIP);
	void packetMaxStuff(int type, std::string adrsIP, sf::TcpSocket& socketServ);
}