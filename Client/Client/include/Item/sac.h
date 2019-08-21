#ifndef DEF_SAC
#define DEF_SAC

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Item/item.h>
#include <Item/enchant.h>
#include <Item/stuff.h>

class sac : public item {
public:
	sac();
	sac(int ID, sf::Vector2i size);
	~sac();

	sf::Vector2i getSize() const;
	int getNbItem() const;
	std::vector<sf::Vector2i> getPosItem() const;

	bool isFull();
	bool posUse(sf::Vector2i pos);
	template<class T, class... Args>
	bool addObject(sf::Vector2i pos, Args&&... args);
	template<class T, class... Args>
	bool addObject(Args&&... args);

	void inPacket(sf::Packet& packet);
	friend sf::Packet& operator<<(sf::Packet& packet, sac& sac_);
	friend sf::Packet& operator>>(sf::Packet& packet, sac& sac);
private:
	void itemInPacket(sf::Packet& packet);	
	sf::Vector2i m_size;
	int m_sizeTotal, m_nbItem;
	std::vector<std::unique_ptr<item>> m_item;
	std::vector<sf::Vector2i> m_posItem;
};

#include <Item/sac.inl>

#endif