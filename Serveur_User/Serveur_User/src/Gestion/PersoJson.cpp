#include <Gestion/PersoJson.h>

namespace gjs {
	void genListPerso(std::vector<std::unique_ptr<Perso>>& listPerso, int ID, std::vector<ObjectFile> listObjFile) {
		std::cout << "Generation de la liste de personnage du compte." << std::endl;
		nlohmann::json fjson;
		std::string accFile = "bin/Compte/" + std::to_string(ID) + ".json";
		std::ifstream fichier(accFile.c_str());
		fichier >> fjson;
		int nbPerso = fjson["nb Perso"].get<int>();
		for (int i = 0; i < nbPerso; i++) {
			nlohmann::json pjson = fjson["Personnage"][i].get<nlohmann::json>();
			std::unique_ptr<Perso> perso;
			gjs::genPerso(perso, pjson);
			int nbStuff = pjson["nbStuff"].get<int>();
			for (int i = 0; i < nbStuff; i++) {
				stuff stuff_ = gjs::genStuff(pjson, i, listObjFile);
				perso->equipeStuff(stuff_);
			}
			int nbSac = pjson["nbSac"].get<int>();
			for (int i=0; i < nbSac; i++) {
				nlohmann::json sjson = pjson["Sac"][i].get<nlohmann::json>();
				int ID = sjson["ID"].get<int>();
				sf::Vector2i size(sjson["Size"]["X"].get<int>(), pjson["Size"]["Y"].get<int>());
				std::unique_ptr<sac> sac_ = std::make_unique<sac>(ID, size);
				int nbItem = pjson["nbItem"].get<int>();
				for (int i = 0; i < nbItem; i++) {
					nlohmann::json ijson = sjson[i].get<nlohmann::json>();
					gjs::genItem(ijson, sac_, listObjFile);
				}
				perso->addSac(std::move(sac_));
			}
		}
	}

	void genPerso(std::unique_ptr<Perso>& perso, nlohmann::json& pjson) {
		std::cout << "-> Generation d'un personnage." << std::endl;
		int type = pjson["Type"].get<int>();
		TYPEPERSO typeF = static_cast<TYPEPERSO>(type);
		int ID = pjson["ID"].get<int>();
		std::string name = pjson["Pseudo"].get<std::string>();
		int map = pjson["Map"].get<int>();
		sf::Vector2f pos(pjson["Pos"]["X"].get<float>(), pjson["Pos"]["Y"].get<float>());
		int lvl = pjson["Exp"]["lvl"].get<int>();
		int expAct = pjson["Exp"]["expAct"].get<int>();
		int pv = pvMax(typeF);
		int mana = manaMax(typeF);
		int argBrute = pjson["Argent"].get<int>();
		int cHair = pjson["Color"]["Hair"].get<int>();
		hair::clr cHairF = static_cast<hair::clr>(cHair);
		int cSkin = pjson["Color"]["Skin"].get<int>();
		skin::clr cSkinF = static_cast<skin::clr>(cSkin);
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
		perso = std::make_unique<Perso>(ID, name, map, pos, lvl, expAct, typeF, argBrute, mana, pv, cHairF, cSkinF);
	}

	stuff genStuff(nlohmann::json& pjson, int i, std::vector<ObjectFile> listObjFile) {
		std::cout << "    -> Generation d'une piece de stuff." << std::endl;
		nlohmann::json sjson = pjson["Stuff"][i].get<nlohmann::json>();
		return genStuff(sjson, listObjFile);
	}

	stuff genStuff(nlohmann::json& ijson, std::vector<ObjectFile> listObjFile) { 
		std::cout << "  -> Generation d'une piece de stuff." << std::endl;
		int ID = ijson["ID"].get<int>();
		std::string name = ijson["Name"].get<std::string>();
		int piece = ijson["Piece"].get<int>();
		PIECE pieceF = static_cast<PIECE>(piece);
		int maxSlot = ijson["maxSlot"].get<int>();
		statistic stat = gjs::genStat(ID, listObjFile[1]);
		int lvlMin = ijson["lvlMin"].get<int>();
		stuff stuff_(ID, name, maxSlot, pieceF, lvlMin, stat);
		int nbEnchant = ijson["nbEnchant"].get<int>();
		nlohmann::json ejson = ijson["enchant"].get<nlohmann::json>();
		for (int i = 0; i < nbEnchant; i++) {
			enchant enchant_ = gjs::genEnchant(ejson, listObjFile[2]);
			stuff_.addEnchant(enchant_);
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

	enchant genEnchant(nlohmann::json& ijson, ObjectFile statEnchante) {
		std::cout << "    -> Generation d'un enchante." << std::endl;
		int ID = ijson["ID"].get<int>();
		std::string name = ijson["Name"].get<std::string>();
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

	void genItem(nlohmann::json& ijson, std::unique_ptr<sac>& sac_, std::vector<ObjectFile> listObjFile) {
		std::cout << "  -> Generation d'un item pour le sac." << std::endl;
		int type = ijson["Type"].get<int>();
		sf::Vector2i pos(ijson["pos"]["X"].get<int>(), ijson["pos"]["Y"].get<int>());
		if (type == 0) {
			enchant enchant_ = gjs::genEnchant(ijson, listObjFile[2]);
			sac_->addObject<enchant>(pos, enchant_);
		}
		else if (type == 1) {
			stuff stuff_ = gjs::genStuff(ijson, listObjFile);
			sac_->addObject<stuff>(pos, stuff_);
		}
		else if (type == 2) {
			int ID = ijson["ID"].get<int>();
			sf::Vector2i size(ijson["Size"]["X"].get<int>(), ijson["Size"]["Y"].get<int>());
			std::unique_ptr<sac> sac__ = std::make_unique<sac>(ID, size);
			sac_->addObject<sac>(pos, ID, size);
		}
		else if (type == 3) {
			item item_ = gjs::genItem(ijson);
			sac_->addObject<item>(pos, item_);
		}
	}

	// TO DO fonction de stat
	int pvMax(TYPEPERSO type) {
		return 1;
	}
	int manaMax(TYPEPERSO type) {
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