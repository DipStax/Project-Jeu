#pragma once
#include <Serv_Item/sac.h>

sac::sac() : item(0, "sac", TypeObj::SAC) {}

sac::sac(int ID, sf::Vector2i size) : item(ID, "sac", TypeObj::SAC) {
	m_size = size;
	m_sizeTotal = size.x*size.y;
}

sac::~sac() {}

sf::Vector2i sac::getSize() const { return m_size; }
int sac::getNbItem() const { return m_item.size(); }

bool sac::isFull() {
	if (m_item.size() == m_sizeTotal) {
		return true;
	}
	return false;
}

bool sac::posUse(sf::Vector2i pos) {
	sf::Vector2i pos_;
	for (int y=0; y < m_size.y; y++) {
		for (int x = 0; x < m_size.x; x++) {
			pos_.x = x;
			pos_.y = y;
			if (pos != pos_) {
				return true;
			}
		}
	}
	return true;
}

void sac::inPacket(sf::Packet& packet) {
	packet << (sf::Uint32)m_ID << (sf::Uint8)m_typeObj << (sf::Uint8)m_size.x << (sf::Uint8)m_size.y << (sf::Uint8)m_item.size();
	this->itemInPacket(packet);
}

void sac::inJson(nlohmann::json& json) {
	json["ID"] = m_ID;
	json["TypeObj"] = m_typeObj;
	json["Size x"] = m_size.x;
	json["Size y"] = m_size.y;
	for (int i = 0; i < m_item.size(); i++) {
		nlohmann::json jsonObject;
		jsonObject["Position x"] =m_pos.at(i).x;
		jsonObject["Position y"] = m_pos.at(i).y;
		m_item.at(i)->inJson(jsonObject);
		json["Contenu"] = (jsonObject);
	}
}

sf::Packet& operator<<(sf::Packet& packet, sac& sac_) {
	packet  << (sf::Uint32)sac_.getID() << sac_.getName() << static_cast<sf::Uint8>(sac_.getTypeObj()) << (sf::Uint8)sac_.getSize().x << (sf::Uint8)sac_.getSize().y
			<< (sf::Uint8)sac_.getNbItem();
	sac_.itemInPacket(packet);
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, sac& sac_) {
	sf::Uint32 ID;
	sf::Uint8 nbItem, typeObj, maxSlot, piece;
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
			sf::Uint8 nbEnchant, lvlMin;
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

nlohmann::json& operator<<(nlohmann::json& json, sac& sac_) {
	sac_.inJson(json);
	return json;
}

void sac::itemInPacket(sf::Packet& packet) {
	for (int i=0;i<m_item.size();i++) {
		m_item.at(i)->inPacket(packet);
		packet << (sf::Uint8)m_pos.at(i).x << (sf::Uint8)m_pos.at(i).y;
	}
}

sf::Vector2i sac::posNUseFirst() {
	if (!this->isFull()) {
		sf::Vector2i pos;
		for (int y = 0; y < m_size.y; y++) {
			for (int x = 0; x < m_size.x; x++) {
				sf::Vector2i pos_(x, y);
				if (!this->posUse(pos_)) {
					return pos_;
				}
			}
		}
	}
	return sf::Vector2i(-1, -1);
}