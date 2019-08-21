#pragma once
#include <Serv_Item/sac.h>

template<class T, class... Args>
bool sac::addObject(sf::Vector2i pos, Args&&... args) {
	if (!this->isFull() && !this->posUse(pos)) {
		m_item.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
		m_posItem.emplace_back(pos);
		m_nbItem++;
		return true;
	}
	return false;
}

template<class T, class... Args>
bool sac::addObject(Args&&... args) {
	if (!this->isFull()) {
		m_item.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
		m_nbItem++;
		return true;
	}
	return false;
}
