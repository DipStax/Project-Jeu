#include <Menu/menuMain.h>

namespace mMain {
	void setMenu(std::vector<std::unique_ptr<Bouton>>& listBtn, short adrs) {
		// 1: main menu
		// 2: menu parametre
		// 3: inscription
		// 4: connexion
		// 5: envoie donne serveur du menu precedent (3/4)
		if (listBtn.empty()) {
			if (adrs != 2) {
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(750, 50), "bin/img/txtr.png", 2));
			}
			if (adrs == 1) {
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(50, 50), "bin/img/txtr.png", 3));
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(50, 125), "bin/img/txtr.png", 4));
			}
			else if (adrs == 2) {
				adrs = 1; // parametre
				// TODO 
				// include <Menu/parametre.h>
			}
			else if (adrs == 3) {
				listBtn.emplace_back(std::make_unique<BoutonKey>(sf::Vector2f(50, 50), sf::Vector2f(5, 5), "bin/img/txtr.png", "Pseudo", 12, 24, sf::Color(185, 185, 185, 255)));
				listBtn.emplace_back(std::make_unique<BoutonKeyEmail>(sf::Vector2f(50, 125), sf::Vector2f(5, 5), "bin/img/txtr.png", "E-mail", 60, 24, sf::Color(185, 185, 185, 255)));
				listBtn.emplace_back(std::make_unique<BoutonKey>(sf::Vector2f(50, 200), sf::Vector2f(5, 5), "bin/img/txtr.png", "Mot de passe", 20, 24, sf::Color(185, 185, 185, 255)));
				listBtn.emplace_back(std::make_unique<BoutonKey>(sf::Vector2f(50, 275), sf::Vector2f(5, 5), "bin/img/txtr.png", "Mot de passe", 20, 24, sf::Color(185, 185, 185, 255)));
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(50, 350), "bin/img/txtr.png", 5));
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(50, 425), "bin/img/txtr.png", 1));
			}
			else if (adrs == 4) {
				listBtn.emplace_back(std::make_unique<BoutonKey>(sf::Vector2f(50, 50), sf::Vector2f(5, 5), "bin/img/txtr.png", "Pseudo", 12, 24, sf::Color(185, 185, 185, 255)));
				listBtn.emplace_back(std::make_unique<BoutonKey>(sf::Vector2f(50, 125), sf::Vector2f(5, 5), "bin/img/txtr.png", "Mot de passe", 20, 24, sf::Color(185, 185, 185, 255)));
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(50, 200), "bin/img/txtr.png", 5));
				listBtn.emplace_back(std::make_unique<Bouton>(sf::Vector2f(50, 275), "bin/img/txtr.png", 1));
			}
		}
	}

	int verifEvent(sf::Event event, short& adrs, std::vector<std::unique_ptr<Bouton>>& listBtn, std::vector<sf::Text>& listTxt, sf::RenderWindow& screen) {
		for (auto&& bouton : listBtn) {
			short adrs_tmp = bouton->verif_event(event, sf::Vector2f(sf::Mouse::getPosition(screen)));
			if (adrs_tmp == 5) {	
				return adrs_tmp;
			}
			else if (adrs_tmp != 0) {
				listTxt.clear();
				listBtn.clear();
				adrs = adrs_tmp;
				break;
			}
		}
		return adrs;
	}

	void affErr(std::string error, std::vector<sf::Text>& listTxt, sf::Font& font) {
		if (error != "") {
			listTxt.clear();
			sf::Text text;
			text.setFont(font);
			text.setFillColor(sf::Color::Red);
			text.setCharacterSize(15);
			if (error == "1.1.1.1") {
				text.setString("Mauvaise identifiant");
				text.setPosition(50, 100);
			}
			else if (error == "1.1.1.2") {
				text.setString("Mauvais mot de passe");
				text.setPosition(50, 175);
			}
			else if (error == "1.1.2.1" || error == "1.1.2.3") {
				std::cout << "Error 1.1.2.1: done" << std::endl;
				text.setString("Identifiant incorrecte");
				text.setPosition(50, 100);
			}
			else if (error == "1.1.2.2") {
				text.setString("Mail indisponible");
				text.setPosition(50, 325);
			}
			listTxt.push_back(text);
			if (error == "1.1.2.3") {
				sf::Text text_;
				text_.setFont(font);
				text_.setFillColor(sf::Color::Red);
				text_.setCharacterSize(15);
				text_.setString("Mail indisponible");
				text_.setPosition(50, 325);
				listTxt.push_back(text_);
			}
		}
	}
}