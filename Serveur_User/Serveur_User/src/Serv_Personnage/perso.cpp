#include <Serv_Personnage/perso.h>

Perso::Perso() {}

Perso::Perso(int ID, std::string pseudo, short map, sf::Vector2f pos, short lvl, int expAct, TYPEPERSO type, 
			 int argentBrute, int manaAct, int vieAct, hair::clr hair, skin::clr skin) {
	m_ID = ID;
	m_type = type;
	m_pseudo = pseudo;
	m_mapAct = map;
	m_pos = pos;
	m_lvl = lvl;
	m_expAct = expAct;
	m_argentBrute = argentBrute;
	m_nbStuff = 0;
	m_nbSac = 0;
	m_vieAct = vieAct;
	m_manaAct = manaAct;
	m_clrHair = hair;
	m_clrSkin = skin;
}

Perso::~Perso() {}

int Perso::getID() const { return m_ID; }
std::string Perso::getPseudo() const { return m_pseudo; }
short Perso::getType() const { return m_type; }
short Perso::getMap() const { return m_mapAct; }
sf::Vector2f Perso::getPos() const { return m_pos; }
short Perso::getLevel() const { return m_lvl; }
int Perso::getExpAct() const { return m_expAct; }
int Perso::getArgent() const { return m_argentBrute; }
statistic& Perso::getStat() { return m_stat; }
int Perso::getNbStuff() const { return m_nbStuff; }
std::map<PIECE, stuff> Perso::getStuff() { return m_stuff; }
int Perso::getNbSac() const { return m_nbSac; }
int Perso::getManaAct() const { return m_manaAct; }
int Perso::getVieAct() const { return m_vieAct; }
skin::clr Perso::getClrSkin() const { return m_clrSkin; }
hair::clr Perso::getClrHair() const { return m_clrHair; }

void Perso::setName(std::string name) {
	m_pseudo = name;
}

void Perso::setPos(float x, float y) {
	m_pos = sf::Vector2f(x, y);
}

void Perso::clearStuff() {
	m_stuff.clear();
}

void Perso::changeColor(skin::clr color) {
	m_clrSkin = color;
}

void Perso::changeColor(hair::clr color) {
	m_clrHair = color;
}

void Perso::forceStuff(stuff equip) {
	m_stuff[equip.getPiece()] = equip;
}

bool Perso::equipeStuff(stuff equip) {
	// TO DO
	std::map<PIECE, stuff>::iterator  it = m_stuff.find(equip.getPiece());
	int sac_to_use = 0;
	if (it != m_stuff.end()) {
		for (auto& sac_ : m_sac) {
			if (!sac_->isFull()) {
				break;
			}
			sac_to_use++;
		}
		return false;
	}
	m_sac.at(sac_to_use)->addObject<stuff>(equip);
	return true;

	// TODO FINIR LA FONCTION
}


void Perso::addSac(std::unique_ptr<sac> sac_) {
	if (m_nbSac < 3) {
		m_sac.push_back(std::move(sac_));
		m_nbSac++;
	}
}

void Perso::sacInPacket(sf::Packet& packet) {
	for (int i = 0; i < m_nbSac; i++) {
		m_sac[i].get()->inPacket(packet);
	}
}

sf::Packet& operator<<(sf::Packet& packet, std::unique_ptr<Perso>& perso) {
	packet << (sf::Uint32)perso->getID() << perso->getPseudo() << (sf::Int8)perso->getMap() << (sf::Uint16)perso->getPos().x
		<< (sf::Uint16)perso->getPos().y << (sf::Uint8)perso->getType() << perso->getStat() << (sf::Uint8)perso->getLevel()
		<< (sf::Uint32)perso->getExpAct() << (sf::Uint32)perso->getArgent() << (sf::Uint16)perso->getManaAct() << (sf::Uint16)perso->getVieAct()
		<< static_cast<sf::Uint8>(perso->getClrHair()) << static_cast<sf::Uint8>(perso->getClrSkin());
	packet << (sf::Uint8)perso->getNbStuff();
	for (auto& stuff_ : perso->getStuff()) {
		packet << stuff_.second;
	}
	packet << (sf::Uint8)perso->getNbSac();
	perso->sacInPacket(packet);
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, std::unique_ptr<Perso>& perso) {
	sf::Uint8 nbStuff;
	stuff stuff_;
	packet >> nbStuff;
	for (int i = 0; i < nbStuff; i++) {
		packet >> stuff_;
		perso->forceStuff(stuff_);
	}
	perso->sacOutPacket(packet);
	return packet;
}

std::ostream& operator<<(std::ostream &os, std::unique_ptr<Perso>& perso) {
	perso->write();
	return os;
}

void Perso::write() {
	std::cout << "Name: " << m_pseudo << std::endl;
	std::cout << "ID: " << m_ID << std::endl;
	std::cout << "Level: " << m_lvl << std::endl;
	std::cout << "Vie: " << m_vieAct << "/" << m_vieMax << std::endl;
	std::cout << "Mana: " << m_manaAct << "/" << m_manaMax << std::endl;
	std::cout << "Experience: " << m_expAct << "/" << m_expNextLvl << std::endl;
	std::cout << "Stuff: " << std::endl;
	std::cout << "<------------------>" << std::endl;
	for (auto& stuff_ : m_stuff) {
		std::cout << stuff_.second;
		std::cout << "<------------------>" << std::endl;
	}

}

void Perso::sacOutPacket(sf::Packet& packet) {
	int nbSac, ID, typeObj;
	sf::Vector2i size;
	std::string name;
	packet >> nbSac;
	for (int i = 0; i < nbSac; i++) {
		packet >> ID >> name >> typeObj >> size.x >> size.y;
		std::unique_ptr<sac> sac_ = std::make_unique<sac>(ID, size);
		packet >> *sac_;
	}
}