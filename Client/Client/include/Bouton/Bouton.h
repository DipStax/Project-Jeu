#ifndef DEF_BOUTON
#define DEF_BOUTON

#include <SFML/Graphics.hpp>
#include <iostream>

class Bouton {
public:
	Bouton();
	Bouton(sf::Vector2f pos, std::string str_txtr, short adrs);
	Bouton(sf::Sprite spr, short adrs);
	virtual ~Bouton();
	void setPos(sf::Vector2f pos);
	void setTxtr(std::string txtr);
	void setAdrs(short adrs);
	short verif_event(sf::Event event, sf::Vector2f posC);
	bool isKey();
	void initTexture(std::string str_txtr, sf::Vector2f pos);
	virtual short verifIB(sf::Vector2f posC);
	virtual void entKey(sf::Uint32 key);
	virtual std::string getEntry();
	virtual void draw(sf::RenderWindow& screen);
protected:
	sf::Vector2f m_size;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::FloatRect m_itBox;
	short m_adrs;
	bool m_key=false;
};

#endif