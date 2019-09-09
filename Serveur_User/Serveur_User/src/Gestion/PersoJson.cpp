#include <Gestion/PersoJson.h>

namespace gjs {
	void genListPerso(std::vector<std::unique_ptr<Perso>>& listPerso, int ID, std::vector<ObjectFile> listObjFile) {
		std::cout << "Generation de la liste de personnage du compte." << std::endl;
		std::vector<int> ListIDPerso;
		// acceder a la bdd pour avoir les ID
		for (int IDPerso : ListIDPerso) {
			nlohmann::json json;
			std::string accFile = "bin/Personnage/" + std::to_string(IDPerso) + ".json";
			std::ifstream fichier(accFile.c_str());
			fichier >> json;
			std::unique_ptr<Perso> perso;
			gjs::genPerso(perso, json);
			auto stuff_it = json.find("Stuff");
			if (stuff_it != json.end()) {
				for (auto& stuff_it_ : *stuff_it) {
					stuff stuff_ = gjs::genStuff(stuff_it_, listObjFile);
					perso->forceStuff(stuff_);
				}
			}
			auto sac_it = json.find("Sac");
			if (sac_it != json.end()) {
				for (auto& sac_it_ : *sac_it) {
					int ID = sac_it_["ID"].get<int>();
					sf::Vector2i size(sac_it_["Size x"].get<int>(), sac_it_["Size y"].get<int>());
					std::unique_ptr<sac> sac_ = std::make_unique<sac>(ID, size);
					auto item_it = sac_it_.find("Item");
					if (item_it != json.end()) {
						for (auto& item_it_ : *item_it) {
							gjs::genItemSac(item_it_, sac_, listObjFile);
						}
					}
					perso->addSac(std::move(sac_));
				}
			}
			listPerso.push_back(std::move(perso));
		}
	}

	void genPerso(std::unique_ptr<Perso>& perso, nlohmann::json& json) {
		std::cout << "-> Generation d'un personnage." << std::endl;
		TYPEPERSO type = json["Type"].get<TYPEPERSO>();
		int ID = json["ID"].get<int>();
		std::string name = json["Pseudo"].get<std::string>();
		int map = json["World"]["Map"].get<int>();
		sf::Vector3f pos(json["World"]["Position x"].get<float>(), json["World"]["Position y"].get<float>(), json["World"]["Position z"].get<float>());
		int lvl = json["Exp"]["lvl"].get<int>();
		int expAct = json["Exp Actuelle"].get<int>();
		int pv = pvMax(type, lvl);
		int mana = manaMax(type, lvl);
		int argBrute = json["Argent brute"].get<int>();
		hair::clr cHair = json["Coleur"]["Cheveux"].get<hair::clr>();
		skin::clr cSkin = json["Coleur"]["Peau"].get<skin::clr>();
		/*
		switch (type) {
			case 0:
				perso = std::make_unique<Tank>(...);
			case 1:
				perso = std::make_unique<Epee>(...);
			case 2:
				perso = std::male_unique<Mage>(...);
			*
			default:

		}
		*/
		perso = std::make_unique<Perso>(ID, name, map, pos, lvl, expAct, type, argBrute, mana, pv, cHair, cSkin);
	}

	stuff genStuff(nlohmann::json& json, std::vector<ObjectFile> listObjFile) { 
		std::cout << "  -> Generation d'une piece de stuff." << std::endl;
		int ID = json["ID"].get<int>();
		std::string name = json["Name"].get<std::string>();
		PIECE piece = json["Piece"].get<PIECE>();
		int maxSlot = json["maxSlot"].get<int>();
		statistic stat = gjs::genStat(ID, listObjFile[1]);
		int lvlMin = json["lvlMin"].get<int>();
		stuff stuff_(ID, name, maxSlot, piece, lvlMin, stat);

		auto enchant_it = json.find("Enchant");
		if (enchant_it != json.end()) {
			for (auto& enchant_it_ : *enchant_it) {
				enchant enchant_ = gjs::genEnchant(enchant_it_, listObjFile[2]);
				stuff_.addEnchant(enchant_);
			}
		}
		return stuff_;
	}

	enchant genEnchant(nlohmann::json& pjson, int i, ObjectFile statEnchante) {
		std::cout << "    -> Generation d'un enchante." << std::endl;
		nlohmann::json sjson = pjson["Enchant"][i].get<nlohmann::json>();
		int ID = sjson["ID"].get<int>();
		std::string name = sjson["Name"].get<std::string>();
		statistic stat = gjs::genStat(ID, statEnchante);
		enchant enchant_(ID, name, stat);
		return enchant_;
	}

	enchant genEnchant(nlohmann::json& json, ObjectFile statEnchante) {
		std::cout << "    -> Generation d'un enchante." << std::endl;
		int ID = json["ID"].get<int>();
		std::string name = json["Name"].get<std::string>();
		statistic stat = gjs::genStat(ID, statEnchante);
		enchant enchant_(ID, name, stat);
		return enchant_;
	}

	item genItem(nlohmann::json& ijson) {
		std::cout << "    -> Generation d'un item." << std::endl;
		int ID = ijson["ID"].get<int>();

		std::string name = ijson["Name"].get<std::string>();
		item item_(ID, name);
		return item_;
	}

	void genItemSac(nlohmann::json& json, std::unique_ptr<sac>& sac_, std::vector<ObjectFile> listObjFile) {
		std::cout << "  -> Generation d'un item pour le sac." << std::endl;
		int ID = json["ID"].get<int>();
		int type = json["Type"].get<int>();
		sf::Vector2i pos(json["pos"]["X"].get<int>(), json["pos"]["Y"].get<int>());
		if (type == 0) {
			enchant enchant_ = gjs::genEnchant(json, listObjFile[2]);
			sac_->addObject<enchant>(pos, enchant_);
		}
		else if (type == 1) {
			stuff stuff_ = gjs::genStuff(json, listObjFile);
			sac_->addObject<stuff>(pos, stuff_);
		}
		else if (type == 2) {
			sf::Vector2i size(json["Size"]["X"].get<int>(), json["Size"]["Y"].get<int>());
			std::unique_ptr<sac> sac__ = std::make_unique<sac>(ID, size);
			sac_->addObject<sac>(pos, ID, size);
		}
		else if (type == 3) {
			item item_ = gjs::genItem(json);
			sac_->addObject<item>(pos, item_);
		}
	}

	// TODO fonction de stat
	int pvMax(TYPEPERSO type, int lvl) {
		return 1;
	}
	int manaMax(TYPEPERSO type, int lvl) {
		return 1;
	}

	statistic genStat(int ID, ObjectFile statStuff) {
		std::cout << "- Generation de stat." << std::endl;
		statistic stat;
		int i=0;
		for (auto& stat_ : statStuff.int_at(ID)) {
			ValType piece = static_cast<ValType>(i);
			stat.setStat(stat_, piece);
			i++;
		}
		return stat;
	}

	void genFileStat(std::vector<ObjectFile> listObjFile) {
		ObjectFile armeFile("./bin/Stat/arme.stat");
		listObjFile.push_back(armeFile);
		ObjectFile stuffFile("./bin/Stat/stuff.stat");
		listObjFile.push_back(stuffFile);
		ObjectFile enchanteFile("./bin/Stat/enchante.stat");
		listObjFile.push_back(enchanteFile);
		std::cout << "Arme:" << std::endl << armeFile << std::endl;
		std::cout << "Stuff:" << std::endl << stuffFile << std::endl;
		std::cout << "Enchante:" << std::endl << enchanteFile;
	}
}