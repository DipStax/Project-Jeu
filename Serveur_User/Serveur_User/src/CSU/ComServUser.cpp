#include <CSU/ComServUser.h>

namespace csu {
	std::vector<int> triatDir(std::string destination) {
		std::istringstream iss(destination);
		std::vector<std::string> v_str_direction((std::istream_iterator<SplitPoint>(iss)), std::istream_iterator<SplitPoint>());
		std::vector<int> direction;
		for (auto&& str_tmp : v_str_direction) {
			direction.push_back(std::stoi(str_tmp));
		}
		return direction;
	}

	void conTry(sf::Packet packetClient, sqlite3* db, std::vector<int>& listCompteCo, std::vector<ObjectFile> listObjFile) {
		std::string str_adrsIP, pseudo, password, dir_serveur;
		std::vector<std::vector<std::string>> info_cb;
		char *errMsg = 0;
		int verif;
		packetClient >> pseudo >> password >> str_adrsIP;
		sf::IpAddress adrsIP(str_adrsIP);
		std::string com = "SELECT * FROM user WHERE pseudo = '" + pseudo + "'";
		std::cout << com << std::endl;
		verif = sqlite3_exec(db, com.c_str(), csu::callback, &info_cb, &errMsg);
		if (verif) {
			std::cout << "Erreur lors de la recherche d'un pseudo dans csu::conTry: " << sqlite3_errmsg(db);
			csu::sendError(adrsIP);
			return;
		}
		sf::Packet packetServ;
		if (info_cb.size() == 1) {
			for (auto&& a : info_cb) {
				if (a[2] == password) {
					int ID = std::stoi(a[0]);
					dir_serveur = "1.1.1.3";
					std::vector<std::unique_ptr<Perso>> listPerso;
					gjs::genListPerso(listPerso, ID, listObjFile);
					packetServ << dir_serveur << ID << listPerso.size();
					for (auto& perso : listPerso) {
						packetServ << perso.get();
					}
					sf::TcpSocket socket;
					sf::Socket::Status status = socket.connect(adrsIP, 40000);
					if (status != sf::Socket::Done) {
						std::cout << "La connexion au client a echoue en voulant envoie le code: 1.1.1.3" << std::endl;
						return;
					}
					socket.send(packetServ);
					std::cout << "Envoie au client (" << adrsIP << ") du code: 1.0.1" << std::endl;
					return;
				}
				else {
					dir_serveur = "1.1.1.2";
				}
			}
		}
		else {
			dir_serveur = "1.1.1.1";
		}
		packetServ << dir_serveur;
		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect(adrsIP, 40000);
		if (status != sf::Socket::Done) {
			std::cout << "La connexion au client a echoue en voulant envoie le code: " << dir_serveur << std::endl;
		}
		socket.send(packetServ);
		std::cout << "Envoie au client (" << adrsIP << ") du code: 1.0.1" << std::endl;
	}

	void renTry(sf::Packet packetClient, sqlite3* db, std::vector<int>& listCompteCo) {
		std::string str_adrsIP, pseudo, password, mail;
		std::vector<std::vector<std::string>> info_cb_pseudo, info_cb_mail, max_id;
		sf::Packet packetServ;
		std::string dir_serveur;
		char *errMsg = 0;
		int verif;
		packetClient >> pseudo >> password >> mail >> str_adrsIP;
		sf::IpAddress adrsIP(str_adrsIP);
		std::string com = "SELECT * FROM user WHERE pseudo = '" + pseudo + "'";
		std::cout << com << std::endl;
		verif = sqlite3_exec(db, com.c_str(), csu::callback, &info_cb_pseudo, &errMsg);
		if (verif) {
			std::cout << "Erreur lors de la recherche d'un pseudo dans csu::renTry: " << sqlite3_errmsg(db);
			csu::sendError(adrsIP);
			return;
		}
		com = "SELECT * FROM user WHERE mail = '" + mail + "'";
		std::cout << com << std::endl;
		verif = sqlite3_exec(db, com.c_str(), csu::callback, &info_cb_mail, &errMsg);
		if (verif) {
			std::cout << "Erreur lors de la recherche d'un mail dans csu::renTry: " << sqlite3_errmsg(db);
			csu::sendError(adrsIP);
			return;
		}
		if (info_cb_pseudo.size() > 0 && info_cb_mail.size() > 0) {
			dir_serveur = "1.1.2.3";
		}
		else if (info_cb_mail.size() > 0) {
			dir_serveur = "1.1.2.2";
		}
		else if (info_cb_pseudo.size() > 0) {
			dir_serveur = "1.1.2.1";
		}
		else {
			dir_serveur = "1.1.2.4";
			com = "INSERT INTO user ('pseudo', 'password', 'mail') VALUES ('" + pseudo + "', '" + password +"', '" + mail +"')";
			std::cout << com << std::endl;
			verif = sqlite3_exec(db, com.c_str(), csu::callback, 0, &errMsg);
			if (verif) {
				std::cout << "Erreur lors de l'ajout d'une nouvelle ligne: " << sqlite3_errmsg(db);
				csu::sendError(adrsIP);
				return;
			}
			com = "SELECT MAX(id) FROM user";
			std::cout << com << std::endl;
			verif = sqlite3_exec(db, com.c_str(), csu::callback, &max_id, &errMsg);
			if (verif) {
				std::cout << "Erreur lors de la recherche du MAX(id): " << sqlite3_errmsg(db);
				csu::sendError(adrsIP);
				return;
			}
			int ID = std::stoi(max_id[0][0]);
			listCompteCo.push_back(ID);
			packetServ << dir_serveur << ID << 0;
			sf::TcpSocket socket;
			sf::Socket::Status status = socket.connect(adrsIP, 40000);
			if (status != sf::Socket::Done) {
				std::cout << "La connexion au client a echoue en voulant envoie le code: " << dir_serveur << std::endl;
				return;
			}
			socket.send(packetServ);
			std::cout << "Envoie au client (" << adrsIP << ") du code: " << dir_serveur << std::endl;			return;
		}
		std::cout << "Plusieur correspondance trouve." << std::endl;
		packetServ << dir_serveur;
		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect(adrsIP, 40000);
		if (status != sf::Socket::Done) {
			std::cout << "La connexion au client a echoue en voulant envoie le code: " << dir_serveur << std::endl;
		}
		socket.send(packetServ);
		std::cout << "Envoie au client (" << adrsIP << ") du code: " << dir_serveur << std::endl;
	}

	void sendError(sf::IpAddress adrsIP) {
		sf::Packet packetServ;
		std::string error = "0";
		packetServ << error;
		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect(adrsIP, 40000);
		if (status != sf::Socket::Done) {
			std::cout << "La connexion au client a echoue en voulant envoie l'erreur: 0" << std::endl;
			return;
		}
		socket.send(packetServ);
		std::cout << "Envoie au client (" << adrsIP << ") d'une erreur du serveur" << std::endl;
	}

	int callback(void *data, int nb, char **contain, char **colName) {
		std::vector<std::vector<std::string>>* info_cb = static_cast<std::vector<std::vector<std::string>>*>(data);
		info_cb->emplace_back(contain, contain + nb);
		return 0; 
	}

	int callbackAff(void* data, int nb, char** contain, char** colName) {
		for (int i = 0; i < nb; i++) {
			std::cout << colName[i] << ": " << (contain[i] ? contain[i] : "NULL") << "  ||  ";
		}
		std::cout << std::endl;
		return 0;
	}

	bool verifPerso(sf::Packet& packet, sqlite3* db, std::unique_ptr<Perso>& perso, int& IDcompte, std::string& adrsIP) {
		std::unique_ptr<Perso> perso_tmp;
		stuff stuff_;
		int ID, map, lvl, expAct, type, argentBrute, manaAct, vieAct;
		std::string pseudo;
		sf::Vector3f pos;
		int colorHair, colorSkin;
		packet >> IDcompte >> ID >> pseudo >> map >> pos.x >> pos.y >> pos.z >> lvl >> expAct >> type >> argentBrute
			   >> manaAct >> vieAct >> colorHair >> colorSkin;
		TYPEPERSO typeF = static_cast<TYPEPERSO>(type);
		hair::clr colorHairF = static_cast<hair::clr>(colorHair);
		skin::clr colorSkinF = static_cast<skin::clr>(colorSkin);
		switch (typeF) {
			case PERSO:
				perso = std::make_unique<Perso>(ID, pseudo, map, pos, lvl, expAct, typeF, argentBrute, manaAct, vieAct, colorHairF, colorSkinF);
				break;
		//case TANK:
		//case EPEE:
		//case MAGE:
		}
		packet >> perso >> adrsIP;
		char* errMsg;
		std::vector<std::vector<std::string>> info_cb_persoAcc;
		std::string com = "SELECT * FROM perso WHERE IDCompe = '" + std::to_string(IDcompte) + "'";
		std::vector<std::vector<std::string>> info_cb_pseudo;
		int verif = sqlite3_exec(db, com.c_str(), csu::callback, &info_cb_persoAcc, &errMsg);
		if (verif) {
			std::cout << "Erreur lors de la recherche du pseudo: " << sqlite3_errmsg(db);
			csu::sendError(adrsIP);
			return false;
		}
		if (info_cb_persoAcc.size() > 0) {
			// trop de personnage
			sf::Packet packetServ;
			std::string dir = "1.2.1.2";
			packetServ << dir << false;
			sf::TcpSocket socket;
			sf::Socket::Status status = socket.connect(adrsIP, 40000);
			if (status != sf::Socket::Done) {
				std::cout << "La connexion au client a echoue en voulant envoie le code: " << dir << std::endl;
				return false;
			}
			socket.send(packetServ);
			return false;
		}
		com = "SELECT * FROM perso WHERE pseudo = '" + pseudo + "'";
		verif = sqlite3_exec(db, com.c_str(), csu::callback, &info_cb_pseudo, &errMsg);
		if (verif) {
			std::cout << "Erreur lors de la recherche du pseudo: " << sqlite3_errmsg(db);
			csu::sendError(adrsIP);
			return false;
		}
		if (info_cb_pseudo.size() > 0) {
			// pseudo deja utilise
			sf::Packet packetServ;
			std::string dir = "1.2.1.1";
			packetServ << dir;
			sf::TcpSocket socket;
			sf::Socket::Status status = socket.connect(adrsIP, 40000);
			if (status != sf::Socket::Done) {
				std::cout << "La connexion au client a echoue en voulant envoie le code: " << dir << std::endl;
				return false;
			}
			socket.send(packetServ);
			return false;
		}
		sf::Packet packetServ;
		std::string dir = "1.2.1.3";
		packetServ << dir;
		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect(adrsIP, 40000);
		if (status != sf::Socket::Done) {
			std::cout << "La connexion au client a echoue en voulant envoie le code: " << dir << std::endl;
			return false;
		}
		socket.send(packetServ);
		return true;
	}
}

std::istream& operator>>(std::istream& is, SplitPoint& output) {
	std::getline(is, output, '.');
	return is;
}

