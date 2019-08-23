#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <array>
#include <Menu/menuMain.h>
#include <Menu/menuCompte.h>
#include <Bouton/BoutonKeyEmail.h>
#include <Item/item.h>
#include <Personnage/perso.h>
#include <Reseau/clientToServ.h>
#include <Reseau/servToClient.h>

#define IPSERV "127.0.0.1"
#define SOSERV 53000
#define SOCLIENT 40000

int main() {
	sf::RenderWindow screen(sf::VideoMode(900, 500), "Jeu");
	screen.setActive();
	screen.setPosition(sf::Vector2i(500, 500));
	short adrs = 1, adrs_tmp = 1;
	bool mMain = true, mCompte = false;
	std::vector<std::unique_ptr<Bouton>> listBtn;
	std::vector<std::unique_ptr<Perso>> listPerso;
	std::unique_ptr<Perso> perso;
	std::vector<sf::Text> listText;
	std::vector<sf::Texture> listTxtr;
	std::vector<sf::Sprite> listSprite;

	std::array<int, 5> creaPerso = { 0, 0, 0, 1, 2};
	std::string dirError;
	int accID;

	sf::Font fontRobotRegular;
	fontRobotRegular.loadFromFile("bin/font/Roboto-Regular.ttf");

	sf::Packet packet;
	sf::TcpListener listener;
	sf::TcpSocket servReceive, servSend;
	std::string adrsIP;
	servSend.connect(IPSERV, SOSERV);
	if (listener.listen(SOCLIENT) != sf::Socket::Done) {
		return 1;
	}
	std::cout << "Listen: Done" << std::endl;
	adrsIP = stc::tryCo(servReceive, servSend, listener);
	if (adrsIP == "false") {
		return 2;
	}
	std::cout << "Adresse IP recu: " << adrsIP << std::endl;

	while(screen.isOpen()) {
		sf::Event event;
		if (mMain) {
			mMain::setMenu(listBtn, adrs);
		}
		else if (mCompte) {
			mCompte::setMenu(listBtn, listPerso, listTxtr, creaPerso, adrs, perso, adrsIP, servSend, servReceive, listener);
			if (listSprite.empty() && adrs == 4) {
				listSprite.emplace_back(listTxtr[0]);
				listSprite.back().setPosition(412.5, 75);
				listSprite.back().setTextureRect(sf::IntRect(75 * creaPerso[0], 0, 75, 75));
				listSprite.emplace_back(listTxtr[1]);
				listSprite.back().setPosition(713, 75);
				listSprite.back().setTextureRect(sf::IntRect(75 * creaPerso[1], 0, 75, 75));
				perso->changeColor(static_cast<hair::clr>(creaPerso[0]));
				perso->changeColor(static_cast<skin::clr>(creaPerso[1]));
				std::cout << "Mise a jour des sprites." << std::endl;
				std::cout << "-> Mise a jour de la couleur du personnage." << std::endl;
				std::cout << perso << std::endl;
			}
		}
		while (screen.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				screen.close();
			}
			if (mMain) {
				mMain::setMenu(listBtn, adrs);
				adrs_tmp = mMain::verifEvent(event, adrs, listBtn, listText, screen);
				if (adrs_tmp == 5) {
					if ((adrs == 3 && listBtn[3]->getEntry() == listBtn[4]->getEntry()) || adrs == 4) {
						packet = cts::genPacCo(adrs, listBtn, adrsIP);
						servSend.connect(IPSERV, SOSERV);
						servSend.send(packet);
						if (listener.accept(servReceive) != sf::Socket::Done) {
							std::cout << "error" << std::endl;
							return 3;
						}
						servReceive.receive(packet);
						accID = stc::AccGen(listPerso, packet, dirError);
						std::cout << accID << std::endl;
						if (accID == 0) {
							mMain::affErr(dirError, listText, fontRobotRegular);
						}
						else {
							mMain = false;
							mCompte = true;
							listBtn.clear();
							listText.clear();
							listSprite.clear();
							adrs = 1;
							listTxtr = mCompte::genTexture();
						}
						adrs_tmp = 0;
					}
				}
			}
			else if (mCompte) {
				adrs_tmp = mCompte::verifEvent(event, adrs, listBtn, listSprite, screen);
				mCompte::boutonInput(adrs_tmp, adrs, listSprite, listBtn, creaPerso);
				// TODO
				// gestion de la validation
			}
		}
		screen.clear(sf::Color::White);
		for (auto& bouton : listBtn) {
			bouton->draw(screen);
		}
		for (auto& text : listText) {
			screen.draw(text);
		}
		for (auto& sprite : listSprite) {
			screen.draw(sprite);
		}
		if (mCompte && adrs == 4 && adrs_tmp != 4) {
			// affiche quand a une MaJ, event ctach: plus affichage
			perso->draw(screen);
		}
		screen.display();
	}
	
	return 0;
}