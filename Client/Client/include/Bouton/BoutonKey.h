#ifndef DEF_BOUTONKEY
#define DEF_BOUTONKEY

#include <Bouton/Bouton.h>

class BoutonKey : public Bouton {
public:
	BoutonKey(sf::Vector2f pos, sf::Vector2f posTxt, std::string str_txtr, std::string txt_def, short txt_max_size, short cara_size, sf::Color color);
	BoutonKey(sf::Sprite spr, sf::Vector2f posTxt, std::string txt_def, short txt_max_size, short cara_size, sf::Color color);
	virtual ~BoutonKey();
	void setPosTxt(sf::Vector2f posTxt);
	void setDefaultText(std::string txt_def);
	void setMaxSize(short txt_max_size);
	void setCaraSize(short cara_size);
	void setColor(sf::Color color);
	short verifIB(sf::Vector2f posC);
	void initTexte(sf::Vector2f posTxt, std::string txt_def, short size, sf::Color color);
	void updateTxt();
	void entKey(sf::Uint32 key);
	virtual std::string getEntry();
	void draw(sf::RenderWindow& screen);
protected:
	std::string m_text_act;
	std::string m_text_def;
	sf::Text m_text_aff;
	sf::Font m_font;
	short m_max_size;
	bool m_txt_ent;
};

#endif