#pragma once
#include <SFML/Network.hpp>
#include <sqlite3.h>
#include <iostream>
#include <sstream>
#include <Serv_Personnage/perso.h>
#include <Gestion/PersoJson.h>

class SplitPoint : public std::string {};

std::istream& operator>>(std::istream& is, SplitPoint& output);

namespace csu {
	extern int callback(void *data, int nb, char **contain, char **colName);
	extern int callbackAff(void *data, int nb, char **contain, char **colName);
	
	std::vector<int> triatDir(std::string destination);
	void conTry(sf::Packet packetClient, sqlite3* db, std::vector<int>& listCompteCo, std::vector<ObjectFile> listObjFile);
	void renTry(sf::Packet packetClient, sqlite3* db, std::vector<int>& listCompteCo);

	void sendError(sf::IpAddress adrsIP);

	bool verifPerso(sf::Packet& packet, sqlite3* db, std::unique_ptr<Perso>& perso, int& IDcompte, std::string& adrsIP);
}


//
//		Direction "1": serveur UserDB
//			Direction ".0": nouvelle connexion
//			-> Adresse IP
//			Retour:
//				-"1.0.1": connexion reussi
//			Direction ".1": generation du compte
//				Direction ".1": connexion
//				-> identifiant
//				-> passWord
//				-> Adresse IP
//				Retour possible:
//					-"1.1.1.1": identifiant incorrecte
//					-"1.1.1.2": identifiant bon, passWord incorrecte
//					-"1.1.1.3": tout est bon
//						-> envoie des persos									
//				Direction ".2": inscription
//				-> identifiant
//				-> passWord
//				-> email
//				-> Adresse IP
//				Retour possible:
//					-"1.1.2.1": identifiant indisponible
//					-"1.1.2.2": email indisponible
//					-"1.1.2.3": les 2 sont indisponible
//					-"1.1.2.4": tout est bon
//						+ ID compte [int]
//						!-> Ajoute dans la BDD
//		Direction ".2": gestion des personnages
//			Direction ".1": cree un personnage
//			-> ID compte
//			-> Perso
//			-> Adresse IP
//			Retour:
//				-"1.2.1.1": pseudo deja utilise
//				-"1.2.1.2": personnage bien genere
//				!-> Ajout du personnage dans le fichier JSON du compte
//				!-> envoie du code "2.1"
//					-> ID compte
//					-> ID perso
//					-> Adresse IP
//			Direction ".2": choisir un personnage
//			-"1.2.2.1"
//				-> ID perso
//				-> Adresse IP
//			Direction ".3": recupere le stuff max
//			-> Type perso
//			-> Adresse IP
//			Retour:
//				-"1.2.3.1": 
//					-> stuff max du type de perso