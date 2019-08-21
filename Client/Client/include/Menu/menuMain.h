#include <iostream>
#include <vector>
#include <Bouton/BoutonKeyEmail.h>

namespace mMain {
	void setMenu(std::vector<std::unique_ptr<Bouton>>& listBtn, short adrs);
	int verifEvent(sf::Event event, short& adrs, std::vector<std::unique_ptr<Bouton>>& list_btn, std::vector<sf::Text>& listTxt, sf::RenderWindow& screen);
	void affErr(std::string error, std::vector<sf::Text>& listTxt, sf::Font& font);
}