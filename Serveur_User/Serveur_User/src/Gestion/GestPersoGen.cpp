#include <Gestion/GestPersoGen.h>

namespace gpg {
	void addMinStuff(std::unique_ptr<Perso>& perso, std::string adrsIP) {
		std::cout << "Ajout du stuff minimum au personnage cree." << std::endl;
		std::vector<stuff> listStuff = gpg::genStuffMin(perso->getType());
		sf::Packet packet;
		std::string dir = "1.2.1.1";
		packet << dir;
		perso->clearStuff();
		for (auto& stuff_ : listStuff) {
			packet << stuff_;
			perso->forceStuff(stuff_);
		}
		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect(adrsIP, 40000);
		if (status != sf::Socket::Done) {
			std::cout << "!-> La connexion au client a echoue en voulant envoie le code: " << dir << std::endl;
		}
		socket.send(packet);
		std::cout << "-> Envoie au client (" << adrsIP << ") du code: 1.2.1.1" << std::endl;
	}

	void savePerso(std::unique_ptr<Perso>& perso, int IDcompte, sqlite3* db) {
		nlohmann::json json;
		json << perso;
		// TODO
		// operateur<<
		// json << perso;

		// enregistre dans la base de donnée Game table 'perso'
	}

	void sendMaxStuff(sf::Packet& packet) {
		std::cout << "Envoie du stuff max au client" << std::endl;
		int type;
		std::string str_adrsIP;
		packet >> type >> str_adrsIP;
		packet.clear();
		std::string dir = "1.2.3.1";
		packet << dir;
		std::vector<stuff> listStuff = gpg::genStuffMax(type);
		packet << listStuff.size();
		for (auto& stuff_ : listStuff) {
			std::cout << stuff_;
			packet << stuff_;
		}
		sf::TcpSocket socket;
		sf::IpAddress adrsIP(str_adrsIP);
		sf::Socket::Status status = socket.connect(adrsIP, 40000);
		if (status != sf::Socket::Done) {
			std::cout << "!-> La connexion au client a echoue en voulant envoie le code: " << dir << std::endl;
			return; // TO DO envoie un message d'erreur
		}
		socket.send(packet);
		std::cout << "-> Envoie au client (" << str_adrsIP << ") du code: 1.2.3.1" << std::endl;
	}

	std::vector<stuff> genStuffMin(int type) {
		std::cout << "Generation du stuff minimum." << std::endl;
		std::vector<stuff> listStuff;
		std::vector<std::vector<std::string>> wordStuff = gpg::genWord("./bin/Data/stuff.min");
		std::string strType = std::to_string(type);
		for (auto& line : wordStuff) {
			if (line[2] == strType) {
				stuff stuff_ = gpg::genStuffLine(line);
				listStuff.push_back(stuff_);
			}
		}
		return listStuff;
	}

	std::vector<stuff> genStuffMax(int type) {
		std::cout << "Generation du stuff maximum." << std::endl;
		std::vector<stuff> listStuff;
		std::vector<std::vector<std::string>> wordStuff = gpg::genWord("./bin/Data/stuff.max");
		for (auto& line : wordStuff) {
			for (auto& word : line) {
				std::cout << word << " : ";
			}
			std::cout << std::endl;
		}
		std::string strType = std::to_string(type);
		for (auto& line : wordStuff) {
			if (line[2] == strType) {
				stuff stuff_ = gpg::genStuffLine(line);
				std::cout << "< - - - - >" << std::endl << stuff_ << std::endl << "< - - - - >" << std::endl;
				listStuff.push_back(stuff_);
			}
		}
		return listStuff;
	}

	std::vector<std::vector<std::string>> genWord(std::string path) {
		std::cout << "Parsage du contenu du ficher: " << path << std::endl;
		std::ifstream file(path);
		std::vector<std::vector<std::string>> word;
		std::string line;
		while (std::getline(file, line)) {
			if (line.empty()) {
				continue;
			}
			std::istringstream iss(line);
			std::vector<std::string> splitLine((std::istream_iterator<SplitPointDot>(iss)), std::istream_iterator<SplitPointDot>());
			word.push_back(splitLine);
		}
		if (!word.empty()) {
			word.erase(word.begin());
		}
		return word;
	}

	stuff genStuffLine(std::vector<std::string> line) {
		std::cout << "Generation du stuff grace au fichier." << std::endl;
		int ID = std::stoi(line[0]);
		int maxSlot = std::stoi(line[3]);
		int piece = std::stoi(line[4]);
		PIECE piece_ = static_cast<PIECE>(piece);
		int minLvl = std::stoi(line[5]);
		std::istringstream iss(line[6]);
		std::vector<std::string> splitSlash((std::istream_iterator<SplitSlash>(iss)), std::istream_iterator<SplitSlash>());
		statistic stat;
		std::cout << "stat: ";
		for (int i=0; i < splitSlash.size(); i++) {
			std::cout << splitSlash[i] << " : ";
			stat.setStat(std::stoi(splitSlash[i]), static_cast<ValType>(i));
		}
		std::cout << std::endl;
		stuff stuff_(ID, line[1], maxSlot, piece_, minLvl);
		stuff_.addStat(stat);
		return stuff_;
	}
}

std::istream& operator>>(std::istream& is, SplitPointDot& output) {
	std::getline(is, output, ';');
	return is;
}

std::istream& operator>>(std::istream& is, SplitSlash& output) {
	std::getline(is, output, '/');
	return is;
}