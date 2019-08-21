#include <Gestion/GestionBdd.h>

namespace gbd {
	void genStuffMaxTable(sqlite3* dbItem) {
		char *errMsg = 0;
		int verif;
		std::string com = "CREATE TABLE IF NOT EXISTS stuffMax ( 'ID' INTEGER PRIMARY KEY AUTOINCREMENT, '\
						   nom' varchar(12) NOT NULL, 'type' INTEGER NOT NULL);";
		std::cout << com << std::endl;
		verif = sqlite3_exec(dbItem, com.c_str(), csu::callbackAff, 0, &errMsg);
		if (verif) {
			std::cout << "Erreur lors de la création de la table 'stuffMax': " << sqlite3_errmsg(dbItem) << std::endl;
			return;
		}
		std::cout << "Verif table: 'stuffMax' -> Done" << std::endl;
		com = "SELECT MAX(ID) FROM stuffMax";
		std::cout << com << std::endl;
		std::vector<std::vector<std::string>> maxID;
		verif = sqlite3_exec(dbItem, com.c_str(), csu::callback, &maxID, &errMsg);
		if (verif) {
			std::cout << "Erreur lors de la création de la table 'stuffMax': " << sqlite3_errmsg(dbItem) << std::endl;
			return;
		}
		if (maxID.size() > 0) {
			// TODO
			// recuperation depuis un fichier
		}

		
	}
}