#include <SFML/Network.hpp>
#include <iostream>

#include <CSR/ComServMast.h>

#define LOCALSO 53000
#define USERSERVSO 53001
#define WORLDSERVSO 53002
#define USERSOCKET 40000

int main() {
	system("TITLE Serveur Master");
	sf::TcpListener serveur;
	serveur.listen(LOCALSO);

	while (true) {
		sf::TcpSocket client;
		sf::Packet packetClient;
		std::string destination;


		serveur.accept(client);
		client.receive(packetClient);
		if (packetClient >> destination) {
			sf::IpAddress adrsIP = client.getRemoteAddress();
			std::cout << "Connexion: " << adrsIP << std::endl << "destination: " << destination << std::endl;
			if (destination == "1.0") {
				cms::rtnIP(client.getRemoteAddress());
			}
			else if (destination[0] == '1') {
				cms::sendToUserDB(packetClient, adrsIP);
			}
			else if (destination[0] == '2') {
				cms::sendToWorld(packetClient, adrsIP);
			}
			std::cout << "Done: " << adrsIP << " -> " << destination << std::endl;
		} 
		else {
			cms::rtnPacketError(client.getRemoteAddress());
		}
	}


	return 0;
}