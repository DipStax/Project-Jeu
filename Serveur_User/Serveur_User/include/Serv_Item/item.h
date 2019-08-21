#ifndef DEF_ITEM
#define DEF_ITEM

#include <SFML/Graphics.hpp>
#include <SFML/Network/Packet.hpp>
#include <iostream>

enum PIECE { PIED, JAMBE, TORSE, MAIN, TETE, ARME, ARMESEC };
enum TypeObj { ENCH, STUFF, SAC, ITEM };

class item {
public:
	item();
	item(int ID, std::string name, TypeObj typeObj = TypeObj::ITEM);
	virtual ~item();

	int getID();
	TypeObj getTypeObj() const;
	std::string getName() const;

	void setID(int ID);
	void setTypeObj(TypeObj typeObj);
	void setName(std::string name);

	virtual void inPacket(sf::Packet& packet);
	friend sf::Packet& operator<<(sf::Packet& packet, item& item_);
	friend sf::Packet& operator>>(sf::Packet& packet, item& item);
	friend std::ostream& operator<<(std::ostream &os, item& perso);
protected:
	virtual void write();
	int m_ID;
	std::string m_name;
	TypeObj m_typeObj;
};

#endif