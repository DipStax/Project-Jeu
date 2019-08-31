#pragma once
#include <sqlite3.h>
#include <Json.hpp>
#include <iostream>
#include <fstream>
#include <Serv_Personnage/perso.h>
#include <Gestion/ObjectFile.h>


namespace gjs {
	void genListPerso(std::vector<std::unique_ptr<Perso>>& listPerso, int ID, std::vector<ObjectFile> listObjFile);
	void genPerso(std::unique_ptr<Perso>& perso, nlohmann::json& pjson);

	stuff genStuff(nlohmann::json& ijson, std::vector<ObjectFile> listObjFile);
	enchant genEnchant(nlohmann::json& pjson, int i, ObjectFile statEnchante);
	enchant genEnchant(nlohmann::json& ijson, ObjectFile statEnchante);
	item genItem(nlohmann::json& ijson);
	void genItemSac(nlohmann::json& ijson, std::unique_ptr<sac>& sac_, std::vector<ObjectFile> listObjFile);

	int pvMax(TYPEPERSO type, int lvl);
	int manaMax(TYPEPERSO type, int lvl);
	statistic genStat(int ID, ObjectFile stat);

	void genFileStat(std::vector<ObjectFile> listObjFile);
}