#include <iostream>
#include <vector>
#include <array>
#include <Bouton/BoutonKey.h>
#include <Personnage/perso.h>
#include <Reseau/clientToServ.h>
#include <Reseau/servToClient.h>

namespace mCompte {
	void setMenu(std::vector<std::unique_ptr<Bouton>>& listBtn, std::vector<std::unique_ptr<Perso>>& listPerso,
				 std::vector<sf::Texture>& listTxtr, std::array<int, 5>& creaPerso, short adrs,
				 std::unique_ptr<Perso>& perso, std::string adrsIP, sf::TcpSocket& socketServ,
				 sf::TcpSocket& servReceive, sf::TcpListener& listener);
	std::vector<sf::Texture> genTexture();
	void boutonInput(int adrs_tmp, int adrs, std::vector<sf::Sprite>& listSprite, 
		std::vector<std::unique_ptr<Bouton>>& listBtn,std::array<int, 5>& creaPerso);
	int verifEvent(sf::Event event, short& adrs, std::vector<std::unique_ptr<Bouton>>& listBtn,
		std::vector<sf::Sprite>& listSprite, sf::RenderWindow& screen);
	void genPersoDemo(std::unique_ptr<Perso>& perso, std::array<int, 5> creaPerso);
	sf::Texture genTxtrSelect(std::unique_ptr<Perso>& perso);
	void persoVerif(std::unique_ptr<Perso>& perso, short& adrs_tmp, int IDCompte, std::string adrsIP,
		sf::TcpSocket& socketServ, sf::TcpSocket& servReceive, sf::TcpListener& listener);
}