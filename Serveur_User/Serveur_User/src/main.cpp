#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <sqlite3.h>
#include <Json.hpp>

#include <iostream>
#include <list>

#include <CSU/ComServUser.h>
#include <Gestion/PersoJson.h>
#include <Gestion/GestPersoGen.h>
#include <Gestion/GestionBdd.h>
#include <Gestion/ObjectFile.h>

#define IPSERVMAST "localhost"
#define LOCALSO 53001

void dump() {
	while (true) {
		std::string com;
		std::getline(std::cin, com);
		if (com[0] == 's' && com[1] == 'y' && com[2] == 's' && com[3] == '?') {
			com.erase(0, 4);
			system(com.c_str());
		}
		else if (com[0] == 's' && com[1] == 'q' && com[2] == 'l' && com[3] == '?') {
			com.erase(0, 4);
			sqlite3 *db;
			char *errMsg = 0;
			int verif;
			verif = sqlite3_open("./bin/Data/Game.db", &db);
			if (verif) {
				std::cout << "Erreur lors de de l'ouverture de la base de donne: " << sqlite3_errmsg(db);
			}
			verif = sqlite3_exec(db, com.c_str(), csu::callbackAff, 0, &errMsg);
			if (verif) {
				std::cout << "Erreur lors de la selection de toute les données de 'user': " << sqlite3_errmsg(db) << std::endl;
			}
		}
	}
}

int main() {
	// arme || stuff || enchante
	
	std::vector<ObjectFile> listObjFile;
	gjs::genFileStat(listObjFile);
	
	system("TITLE Serveur User");
	std::vector<int> listCompteCo;

	sqlite3 *db;
	char *errMsg = 0;
	int verif = sqlite3_open("./bin/Data/Game.db", &db);
	if (verif) {
		std::cout << "Erreur lors de de l'ouverture de la base de donne 'Game': " << sqlite3_errmsg(db);
	}
	else {
		std::cout << "Verif table: 'Game' -> Done" << std::endl;
	}

	// User:
	// ID || pseudo || password || mail
	std::string com = "CREATE TABLE IF NOT EXISTS user ( 'ID' INTEGER PRIMARY KEY AUTOINCREMENT, 'pseudo' varchar(12) NOT NULL, 'password' text NOT NULL, 'mail' text NOT NULL);";
	std::cout << com << std::endl;
	verif = sqlite3_exec(db, com.c_str(), csu::callback, 0, &errMsg);
	if (verif) {
		std::cout << "Erreur lors de la création de la table 'user': " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "Verif table: 'user' -> Done" << std::endl;
	}

	// Perso
	// ID || pseudo || ID compte
	com = "CREATE TABLE IF NOT EXISTS perso ( 'ID' INTEGER PRIMARY KEY AUTOINCREMENT, 'pseudo' varchar(12) NOT NULL, 'ID compte' INTEGER NOT NULL);";
	std::cout << com << std::endl;
	verif = sqlite3_exec(db, com.c_str(), csu::callback, 0, &errMsg);
	if (verif) {
		std::cout << "Erreur lors de la création de la table 'user': " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "Verif table: 'perso' -> Done" << std::endl;
	}
	std::cout << std::endl << std::endl << "<------------------------->" << std::endl;

	sf::TcpListener serveur;
	serveur.listen(LOCALSO);

	sf::Thread thread(&dump);
	thread.launch();

	while (true) {
		sf::TcpSocket client;
		sf::Packet packet;
		std::string destination;
		int tmp = 0;

		serveur.accept(client);
		client.receive(packet);
		if (packet >> destination) {
			std::cout << "Connexion -> destination: " << destination << std::endl;
			std::vector<int> direction = csu::triatDir(destination);
			if (direction[1] == 1) {
				if (direction[2] == 1) {
					std::cout << "Direction: \"1.1.1.x\"" << std::endl << std::endl;
					csu::conTry(packet, db, listCompteCo, listObjFile); // 1.1.1
				}
				else if (direction[2] == 2) {
					std::cout << "Direction: \"1.1.2.x\"" << std::endl << std::endl;
					csu::renTry(packet, db, listCompteCo); // 1.1.2
				}
			}
			if (direction[1] == 2) {
				std::unique_ptr<Perso> perso;
				int IDcompte;
				std::string adrsIP;
				if (direction[2] == 1) { // 1.2.1
					std::cout << "Direction \"1.2.1.x\"" << std::endl << std::endl;
					if (csu::verifPerso(packet, db, perso, IDcompte, adrsIP)) {
						// TODO
						// enregistre le perso dans le Json et dans la BDD
						// envoie le personnage au serveur world 
						gpg::addMinStuff(perso, adrsIP);
						gpg::savePerso(perso, IDcompte, db);
					}
				}
				if (direction[2] == 2) { // 1.2.2
					// TODO
				}
				else if (direction[2] == 3) { // 1.2.3
					std::cout << "Direction \"1.2.3.x\"" << std::endl << std::endl;
					gpg::sendMaxStuff(packet);
				}
			}
			std::cout << "<------------------------->" << std::endl;
		}
	}

	return 0;
}