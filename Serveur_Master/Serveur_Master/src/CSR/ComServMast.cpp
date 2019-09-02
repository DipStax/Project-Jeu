#include <CSR/ComServMast.h>

namespace cms {
	void rtnPacketError(sf::IpAddress adrsIp) {
		std::cout << "Lecture du packet impossible." << std::endl;
		sf::Packet packet;
		std::string errCode = "erreur";
		packet << errCode;
		sf::TcpSocket client;
		sf::Socket::Status status = client.connect(adrsIp, USERSOCKET);
		if (status != sf::Socket::Done) {
			std::cout << "Erreur lors de l'envoie d'une erreur" << std::endl;
		}
		else {
			client.send(packet);
		}
	}

	void rtnIP(sf::IpAddress adrsIp) {
		sf::Packet packet;
		packet << "1.0.1" << adrsIp.toString();
		sf::TcpSocket client;
		std::cout << adrsIp.toString() << std::endl;
		sf::Socket::Status status = client.connect(adrsIp, USERSOCKET);
		if (status != sf::Socket::Done) {
			std::cout << "Erreur lors du retour d'IP" << std::endl;
		}
		else {
			client.send(packet);
		}
	}
	
	void sendToUserDB(sf::Packet& packetClient, sf::IpAddress adrsIP) {
		sf::TcpSocket serverUser;
		packetClient;
		sf::Socket::Status status = serverUser.connect("127.0.0.1", USERSERVSO);
		if (status != sf::Socket::Done) {
			std::cout << "Envoie au serveur USERDB: echoue." << std::endl;
		}
		else {
			serverUser.send(packetClient);
			std::cout << "Envoie au serveur USERDB: reussie." << std::endl;
		}
	}

	void sendToWorld(sf::Packet& packetClient, sf::IpAddress adrsIP) {
		sf::TcpSocket serverWorld;
		sf::Socket::Status status = serverWorld.connect("127.0.0.1", WORLDSERVSO);
		if (status != sf::Socket::Done) {
			std::cout << "Envoie au serveur WORLD: echoue." << std::endl;
		}
		else {
			serverWorld.send(packetClient);
			std::cout << "Envoie au serveur WORLD: reussie." << std::endl;
		}
	}
}