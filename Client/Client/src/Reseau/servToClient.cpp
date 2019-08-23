#include <Reseau/servToClient.h>

namespace stc {
	std::string tryCo(sf::TcpSocket& servReceive, sf::TcpSocket& servSend, sf::TcpListener& listener) {
		cts::genIP(servSend);
		if (listener.accept(servReceive) != sf::Socket::Done) {
			return "false";
		}
		std::cout << "Accept serveur Receive: Done" << std::endl;
		std::string adrsIP = stc::getIP(servReceive);
		return adrsIP;
	}

	std::string getIP(sf::TcpSocket& servReceive) {
		sf::Packet packet;
		std::string adrsIP, direction;
		servReceive.receive(packet);
		packet >> direction >> adrsIP;
		return adrsIP;
	}

	int AccGen(std::vector<std::unique_ptr<Perso>>& listPerso, sf::Packet& packet, std::string& dirError) {
		int accID, nbPerso;
		packet >> dirError;
		if (dirError == "1.1.1.3") {
			packet >> accID >> nbPerso;
			for (int i = 0; i < nbPerso; i++) {
				std::unique_ptr<Perso> perso_tmp;
				stuff stuff_;
				int ID, map, lvl, expAct, type, argentBrute, manaAct, vieAct;
				std::string pseudo;
				sf::Vector2f pos;
				int colorHair, colorSkin;
				packet >> ID >> pseudo >> map >> pos.x >> pos.y >> lvl >> expAct >> type >> argentBrute
					>> manaAct >> vieAct >> colorHair >> colorSkin;
				TYPEPERSO typeF = static_cast<TYPEPERSO>(type);
				hair::clr colorHairF = static_cast<hair::clr>(colorHair);
				skin::clr colorSkinF = static_cast<skin::clr>(colorSkin);
				switch (type) {
					case 3:
						perso_tmp = std::make_unique<Perso>(ID, pseudo, map, pos, lvl, expAct, typeF, argentBrute, manaAct, vieAct, colorHairF, colorSkinF);
					//case 0:
						//TANK
					//case 1:
						// EPEE
					//case 2:
						// MAGE
				}
				packet >> perso_tmp;
				listPerso.push_back(std::move(perso_tmp));
			}

		}
		else if (dirError == "1.1.2.4") {
			packet >> accID;
		}
		else {
			return 0;
		}
		return accID;
	}

	void receiveMaxStuff(std::unique_ptr<Perso>& perso, sf::TcpSocket& servReceive, sf::TcpListener& listener) {
		sf::Packet packet;
		std::string dir;
		int nbStuff;
		if (listener.accept(servReceive) != sf::Socket::Done) {
			return;
		}
		servReceive.receive(packet);
		packet >> dir >> nbStuff;
		std::cout << "nbStuff val: " << nbStuff << std::endl;
		if (dir != "1.2.3.1") {
			return;
		}
		stuff stuff_;
		for (int i = 0; i < nbStuff; i++) {
			packet >> stuff_;
			std::cout << stuff_ << std::endl;
			perso->forceStuff(stuff_);
		}
	}
}