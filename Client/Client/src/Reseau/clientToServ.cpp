#include <Reseau/clientToServ.h>

namespace cts {
	void genIP(sf::TcpSocket& socketServ) {
		std::string direction = "1.0";
		sf::Packet packet;
		packet << direction;
		socketServ.send(packet);
	}

	sf::Packet genPacCo(short adrs, std::vector<std::unique_ptr<Bouton>>& list_btn, std::string adrsIP) {
		switch (adrs) {
		case 3:
			return cts::packetIns(list_btn, adrsIP);
		case 4:
			return cts::packetCon(list_btn, adrsIP);
		}
		sf::Packet voidPacket;
		return voidPacket;
	}

	sf::Packet packetCon(std::vector<std::unique_ptr<Bouton>>& list_btn, std::string adrsIP) {
		// std::string pseudo = list_btn[1]->getEntry();
		// std::string pw = list_btn[2]->getEntry();
		std::string pseudo = "hugo";
		std::string pw = "hugoboss95";
		std::string direction = "1.1.1";
		sf::Packet packet;
		packet << direction << pseudo << pw << adrsIP;
		return packet;
	}

	sf::Packet packetIns(std::vector<std::unique_ptr<Bouton>>& list_btn, std::string adrsIP) {
		std::string pseudo = list_btn[1]->getEntry();
		std::string mail = list_btn[2]->getEntry();
		std::string pw = list_btn[3]->getEntry();
		std::string direction = "1.1.2";
		sf::Packet packet;
		packet << direction << pseudo << pw << mail << adrsIP;
		return packet;
	}

	void packetMaxStuff(int type, std::string adrsIP, sf::TcpSocket& socketServ) {
		std::string direction = "1.2.3";
		sf::Packet packet;
		packet << direction << type << adrsIP;
		socketServ.connect(IPSERV, SOSERV);
		socketServ.send(packet);
	}

	void persoVerif(std::unique_ptr<Perso>& perso, int IDCompte, std::string adrsIP, sf::TcpSocket& socketServ) {
		std::string direction = "1.2.1";
		sf::Packet packet;
		perso->clearStuff();
		packet << direction << (sf::Uint32)IDCompte << perso << adrsIP;
		socketServ.connect(IPSERV, SOSERV);
		socketServ.send(packet);
	}
}