#include <SFML/Network.hpp>
#include <iostream>

#define LOCALSO 53000
#define USERSERVSO 53001
#define WORLDSERVSO 53002
#define USERSOCKET 40000

namespace cms {
	void rtnPacketError(sf::IpAddress adrsIP);
	void rtnIP(sf::IpAddress);
	void sendToUserDB(sf::Packet& packetClient, sf::IpAddress adrsIP);
	void sendToWorld(sf::Packet& packetClient, sf::IpAddress adrsIP);
}