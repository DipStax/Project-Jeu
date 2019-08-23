#ifndef DEF_PERSO
#define DEF_PERSO

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network/Packet.hpp>
#include <iostream>

#include <Personnage/Stat.h>

#include <Item/item.h>
#include <Item/stuff.h> 
#include <Item/sac.h>

#include <iomanip>

enum TYPEPERSO { TANK, EPEE, MAGE, PERSO };
enum dir { U, D, R, L, UR, RL, DU, DL };
namespace skin {
	enum clr { Blanc, MaronC, MaronF, Beige, Rose, Jaune };
}
namespace hair {
	enum clr { Blanc, Gris, Maron, Rouge, Ornage, Jaune };
}
enum colorZone { SKIN, HAIR };

class Perso {
public:
	Perso();
	Perso(int ID, std::string pseudo, short map, sf::Vector2f pos, short lvl, int expAct, TYPEPERSO type, 
		  int argentBrute, int manaAct, int vieAct, hair::clr hair, skin::clr skin);
	~Perso();

	int getID() const;
	std::string getPseudo() const;
	short getType() const;
	short getMap() const;
	sf::Vector2f getPos() const;
	short getLevel() const;
	int getExpAct() const;
	int getArgent() const;
	statistic& getStat();
	int getNbStuff() const;
	std::map<TypeObj, stuff> getStuff();
	int getNbSac() const;
	int getManaAct() const;
	int getVieAct() const;
	skin::clr getClrSkin() const;
	hair::clr getClrHair() const;

	void changeColor(skin::clr color);
	void changeColor(hair::clr color);

	void forceStuff(stuff equip);
	bool equipeStuff(stuff equip);
	void addSac(std::unique_ptr<sac> sac);
	template<class T, class... Args>
	void addInSac(Args&&... args);

	void draw(sf::RenderWindow& screen);
	void rdTxtrDraw(sf::RenderTexture& rdTxtr);
	void sacInPacket(sf::Packet& packet);
	void sacOutPacket(sf::Packet& packet);
	friend sf::Packet& operator<<(sf::Packet& packet, std::unique_ptr<Perso>& perso);
	friend sf::Packet& operator>>(sf::Packet& packet, std::unique_ptr<Perso>& perso);
	friend std::ostream& operator<<(std::ostream &os, std::unique_ptr<Perso>& perso);
protected:
	void write();
	void initSprite();
	void upSprite();
	std::string m_pseudo;
	short m_lvl, m_NumSprite, m_mapAct;
	sf::Vector2f m_pos;
	statistic m_stat;
	int m_nbStuff, m_nbSac;
	int m_manaAct, m_vieAct;
	int m_manaMax, m_vieMax;
	int m_expAct, m_expNextLvl;
	int m_ID, m_argentBrute;
	const int8_t m_maxSac = 3;
	std::map<TypeObj, stuff> m_stuff;
	std::vector<std::unique_ptr<sac>> m_sac;
	TYPEPERSO m_type;
	hair::clr m_clrHair;
	skin::clr m_clrSkin;
	const short m_maxLvl = 30;
	// Variable du sprite
	
	sf::Texture m_txtrMain;
	sf::Sprite m_sptMain;
	sf::Texture m_txtrPerso;
	sf::Sprite m_sptPerso;
};

#include <Personnage/perso.inl>

#endif