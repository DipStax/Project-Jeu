#ifndef DEF_BOUTONKEYMAIL
#define DEF_BOUTONKEYMAIL

#include <Bouton/BoutonKey.h>

class BoutonKeyEmail : public BoutonKey {
public:
	BoutonKeyEmail(sf::Vector2f pos, sf::Vector2f posTxt, std::string str_txtr, std::string txt_def, short txt_max_size, short cara_size, sf::Color color);
	BoutonKeyEmail(sf::Sprite spr, sf::Vector2f posTxt, std::string txt_def, short txt_max_size, short cara_size, sf::Color color);
	~BoutonKeyEmail();
	void entKey(sf::Uint32 key);
};

#endif