#pragma once
#include <Serv_Item/sac.h>

template<class T, class... Args>
bool sac::addObject(sf::Vector2i pos, Args&&... args) {
	if (!this->isFull() && !this->posUse(pos)) {
		m_item.at(this->transPos(pos)) = std::make_unique<T>(std::forward<Args>(args)...);	
		m_item.push_back(std::make_unique<T>(std::forward<Args>(args)...));
		m_pos.push_back(pos);
		return true;
	}
	return false;
}

template<class T, class... Args>
bool sac::addObject(Args&&... args) {
	if (!this->isFull()) {
		sf::Vector2i pos = this->posNUseFirst();
		m_item.at(this->transPos(pos)) = std::make_unique<T>(std::forward<Args>(args)...);
		return true;
	}
	return false;
}

