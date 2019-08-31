#include <Menu/menuCompte.h>

namespace mCompte {
	void setMenu(std::vector<std::unique_ptr<Bouton>>& listBtn, std::vector<std::unique_ptr<Perso>>& listPerso, 
				 std::vector<sf::Texture>& listTxtr, std::array<int, 5>& creaPerso, short adrs, 
				 std::unique_ptr<Perso>& perso, std::string adrsIP, sf::TcpSocket& socketServ, 
				 sf::TcpSocket& servReceive, sf::TcpListener& listener) {
		// 1: menu compte
		// 2: menu parametre
		// 3: deconnexion
		// 4: menu de creation de personnage
		// 5: validation de la creation
		// 51: creation valide
		// 61: changement de couleur pour les cheveux -
		// 62: changement de couleur pour les cheveux +
		// 71: changement de couleur pour la peau -
		// 72: changement de couleur pour la peau +
		// 8: selection de la classe pos1
		// 9: selection de la classe pos2 (useless)
		// 10: selection de la classe pos3
		// 11: choix pseudo
		// 12: retour
		// 13...: personnage selectionne
		if (adrs == 0) {
			listBtn.clear();
		}
		if (listBtn.empty()) {
			std::cout << "Mise a jour du menu de Compte." << std::endl;
			if (adrs != 2 && adrs != 4) {
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(750, 50), "bin/img/txtr.png", 2));
			}
			if (adrs == 1) {
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(50, 400), "bin/img/txtr.png", 3));
				short nbPerso = listPerso.size();
				for (int i = 0; i < nbPerso; i++) {
					sf::Texture txtrSelect = mCompte::genTxtrSelect(listPerso[i]);
					sf::Sprite sprSelect(txtrSelect);
					sprSelect.setPosition(750., 125 + i * 75.);
					listBtn.emplace_back(std::make_unique<Bouton>(sprSelect, 13+i));
				}
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(750., 125 + nbPerso * 75.), "bin/img/txtr.png", 4));
			}
			if (adrs == 2) {
				adrs = 1; // parametre
				// TODO 
				// include <Menu/parametre.h>
			}
			if (adrs == 4) {
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(775, 445), "bin/img/ctpc.png", 5));;
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(350, 88), "bin/img/cpc.png", 61));
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(500, 88), "bin/img/cpc.png", 62));
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(650, 88), "bin/img/cpc.png", 71));
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(800, 88), "bin/img/cpc.png", 72));

				sf::Sprite spr(listTxtr[2]);
				spr.setTextureRect(sf::IntRect(75 * creaPerso[2], 0, 75, 75));
				spr.setPosition(325, 275);
				listBtn.emplace_back(std::make_unique<Bouton>(spr, 8));
				spr.setTextureRect(sf::IntRect(75 * creaPerso[3], 0, 75, 75));
				spr.setPosition(563, 250);
				listBtn.emplace_back(std::make_unique<Bouton>(spr, 9));
				spr.setTextureRect(sf::IntRect(75 * creaPerso[4], 0, 75, 75));
				spr.setPosition(800, 275);
				mCompte::genPersoDemo(perso, creaPerso);
				cts::packetMaxStuff(creaPerso[3], adrsIP, socketServ);
				stc::receiveMaxStuff(perso, servReceive, listener);
				listBtn.emplace_back(std::make_unique<Bouton>(spr, 10));
				listBtn.emplace_back(std::make_unique<BoutonKey>(sf::Vector2f(450, 425), sf::Vector2f(125, 12), "bin/img/tctpc.png", "Pseudo", 12, 27, sf::Color(185, 185, 185, 255)));
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(325, 445), "bin/img/ctpc.png", 1));
			}
		}
	}

	std::vector<sf::Texture> genTexture() {
		std::cout << "Chargement de texture" << std::endl;
		sf::Texture txtr;
		std::vector<sf::Texture> listTxtr;
		std::vector<std::string> str{
			"bin/img/hairColor.png",
			"bin/img/skinColor.png",
			"bin/img/iconeClasse.png",
		};
		for (auto& str_ : str) {
			txtr.loadFromFile(str_);
			listTxtr.push_back(txtr);
		}
		return listTxtr;
	}

	void boutonInput(int adrs_tmp, int adrs, std::vector<sf::Sprite>& listSprite, 
				     std::vector<std::unique_ptr<Bouton>>& listBtn, std::array<int, 5>& creaPerso) {
		if (adrs == 4) {
			int var;
			switch (adrs_tmp) {
			case 61:
				creaPerso[0]--;
				if (creaPerso[0] < 0) {
					creaPerso[0] = 5;
				}
				listSprite.clear();
				break;
			case 62:
				creaPerso[0]++;
				if (creaPerso[0] > 5) {
					creaPerso[0] = 0;
				}
				listSprite.clear();
				break;
			case 71:
				creaPerso[1]--;
				if (creaPerso[1] < 0) {
					creaPerso[1] = 5;
				}
				listSprite.clear();
				break;
			case 72:
				creaPerso[1]++;
				if (creaPerso[1] > 5) {
					creaPerso[1] = 0;
				}
				listSprite.clear();
				break;
			case 8:
				var = creaPerso[4];
				creaPerso[4] = creaPerso[3];
				creaPerso[3] = creaPerso[2];
				creaPerso[2] = var;
				listBtn.clear();
				listSprite.clear();
				break;
			case 10:
				var = creaPerso[4];
				creaPerso[4] = creaPerso[2];
				creaPerso[2] = creaPerso[3];
				creaPerso[3] = var;
				listBtn.clear();
				listSprite.clear();
			}
		}
	}

	int verifEvent(sf::Event event, short& adrs, std::vector<std::unique_ptr<Bouton>>& listBtn,
				   std::vector<sf::Sprite>& listSprite, sf::RenderWindow& screen) {
		for (auto& btn : listBtn) {
			short adrs_tmp = btn->verif_event(event, sf::Vector2f(sf::Mouse::getPosition(screen)));
			if (adrs_tmp == 5) {
				return adrs_tmp;
			}
			else if (adrs_tmp == 1 || adrs_tmp == 4) {
				listBtn.clear();
				listSprite.clear();
				adrs = adrs_tmp;
				return adrs;
			}
			else if (adrs_tmp != 0) {
				return adrs_tmp;
			}
		}
		return 0;
	}

	sf::Texture genTxtrSelect(std::unique_ptr<Perso>& perso) {
		std::cout << "Generation des textures de selection." << std::endl;
		sf::Texture txtr;
		if (!txtr.loadFromFile("bin/img/txtr.png")) {
			return txtr;
		}
		sf::Sprite bg(txtr);
		sf::RenderTexture rdrTxtr;
		rdrTxtr.create(txtr.getSize().x, txtr.getSize().y);
		rdrTxtr.draw(bg);
		perso->rdTxtrDraw(rdrTxtr);
		rdrTxtr.display();
		return rdrTxtr.getTexture();
	}

	void persoVerif(std::unique_ptr<Perso>& perso, short& adrs_tmp, int IDCompte, std::string adrsIP,
					sf::TcpSocket& socketServ, sf::TcpSocket& servReceive, sf::TcpListener& listener) {
		std::string code;
		cts::persoVerif(perso, IDCompte, adrsIP, socketServ);
		stc::getPersoVerif(servReceive, listener, code);
		if (code == "1.2.1.3") {
			stc::receiveMinStuff(perso, servReceive, listener);
			adrs_tmp = 53;
		}
		else if (code == "1.2.1.2") {
			adrs_tmp = 52;
		}
		else if (code == "1.2.1.1") {
			adrs_tmp = 51;
		}
	}

	void genPersoDemo(std::unique_ptr<Perso>& perso, std::array<int, 5> creaPerso) {
		std::cout << "Creation du personnage." << std::endl;
		hair::clr colorHair = static_cast<hair::clr>(creaPerso[0]);
		skin::clr colorSkin = static_cast<skin::clr>(creaPerso[1]);
		switch (creaPerso[3]) {
		default:
			perso = std::make_unique<Perso>(0, "none", 1, sf::Vector2f(1, 1), 1, 1, TYPEPERSO::PERSO, 1, 1, 1, colorHair, colorSkin);
			break;
			// case 1:
				// TANK
		}
		perso->setPos(50, 50);
	}


}