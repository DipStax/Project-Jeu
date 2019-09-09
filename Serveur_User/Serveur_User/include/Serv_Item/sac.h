#ifndef DEF_SAC
#define DEF_SAC

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <Serv_Item/item.h>
#include <Serv_Item/enchant.h>
#include <Serv_Item/stuff.h>

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
	bool addObject(sf::Vector2i pos, Args&& ... args);
	template<class T, class... Args>
	bool addObject(Args&& ... args);

	void inPacket(sf::Packet& packet);
	void inJson(nlohmann::json& json);
	friend sf::Packet& operator<<(sf::Packet& packet, sac& sac_);
	friend sf::Packet& operator>>(sf::Packet& packet, sac& sac);
	friend nlohmann::json& operator<<(nlohmann::json& json, sac& sac_);
private:
	void itemInPacket(sf::Packet& packet);
	sf::Vector2i posNUseFirst();
	sf::Vector2i transPos(int intPos);
	int transPos(sf::Vector2i vecPos);
	sf::Vector2i m_size;
	int m_sizeTotal;
	std::map<int, std::shared_ptr<item>> m_item;
};

#include <Serv_Item/sac.inl>

#endif