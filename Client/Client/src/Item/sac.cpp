#pragma once
#include <Item/sac.h>

sac::sac() : item(0, "sac", TypeObj::SAC) {}

sac::sac(int ID, sf::Vector2i size) : item(ID, "sac", TypeObj::SAC) {
	m_size = size;
	m_sizeTotal = size.x*size.y;
}

sac::~sac() {}

sf::Vector2i sac::getSize() const { return m_size; }
int sac::getNbItem() const { return m_nbItem; }
std::vector<sf::Vector2i> sac::getPosItem() const { return m_posItem; }

bool sac::isFull() {
	if (m_item.size() == m_sizeTotal) {
		return true;
	}
	return false;
}

bool sac::posUse(sf::Vector2i pos) {
	for (int i = 0; i < m_posItem.size(); i++) {
		if (m_posItem[i].x == pos.x && m_posItem[i].y == pos.y) {
			return true;
		}
	}
	return false;
}

void sac::itemInPacket(sf::Packet& packet) {
	for (int i = 0; i < m_nbItem; i++) {
		m_item[i].get()->inPacket(packet);
		packet << m_posItem[i].x << m_posItem[i].y;
	}
}

void sac::inPacket(sf::Packet& packet) {
	packet << m_ID << m_typeObj << m_size.x << m_size.y << m_nbItem;
	this->itemInPacket(packet);
}

sf::Packet& operator<<(sf::Packet& packet, sac& sac_) {
	packet  << sac_.getID() << sac_.getName() << static_cast<int>(sac_.getTypeObj()) << sac_.getSize().x << sac_.getSize().y
			<< sac_.getNbItem();
	sac_.itemInPacket(packet);
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, sac& sac_) {
	int nbItem, ID, typeObj, maxSlot, piece;
	std::string name;
	sf::Vector2i pos, size;
	statistic stat;
	packet >> nbItem;
	for (int i = 0; i < nbItem; i++) {
		packet >> ID >> name >> typeObj;
		TypeObj typeF = static_cast<TypeObj>(typeObj);

		if (typeObj == 0) {
			packet >> stat >> pos.x >> pos.y;
			enchant enchant_(ID, name, stat);
			sac_.addObject<enchant>(pos, std::move(enchant_));
		}
		else if (typeObj == 1) {
			int nbEnchant, lvlMin;
			packet >> maxSlot >> piece >> lvlMin >> stat;
			PIECE pieceF = static_cast<PIECE>(piece);
			stuff stuff_(ID, name, maxSlot, pieceF, lvlMin, stat);
			packet >> nbEnchant;
			for (int i = 0; i < nbEnchant; i++) {
				packet >> ID >> name >> stat;
				enchant enchant_(ID, name, stat);
				stuff_.addEnchant(enchant_);
			}
			packet >> pos.x >> pos.y;
			sac_.addObject<stuff>(pos, std::move(stuff_));
		}
		else if (typeObj == 2) {
			packet >> size.x >> size.y >> pos.x >> pos.y;
			sac_.addObject<sac>(pos, ID, size);
		}
		else {
			packet >> pos.x >> pos.y;
			item item_(ID, name);
			sac_.addObject<item>(pos, std::move(item_));
		}
	}

	return packet;
}