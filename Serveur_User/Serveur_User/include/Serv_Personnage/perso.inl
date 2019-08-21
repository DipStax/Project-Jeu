#pragma once
#include <Serv_Personnage/perso.h>

template<class T, class... Args>
void Perso::addInSac(Args&&... args) {
	for (int i = 0; i < m_sac.size(); i++) {
		bool verif = m_sac[i].get()->addObject<T>(std::forward<Args>(args)...);
		if (verif) {
			return true;
		}
	}
	return false;
}