#pragma once
#include <sqlite3.h>
#include <iostream>
#include <CSU/ComServUser.h>

namespace gbd {
	void genStuffMaxTable(sqlite3* dbItem);
	// TODO
	// faire la meme pour le stuffMin
}