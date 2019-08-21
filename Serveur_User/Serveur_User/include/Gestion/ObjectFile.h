#ifndef DEF_OBJECTFILE
#define DEF_OBJECTFILE

#pragma once
#include <vector>
#include <string>
#include <fstream>

class ObjectFile {
public:
	ObjectFile(std::string path);
	~ObjectFile();
	void newFile(std::string path);
	friend std::ostream& operator<<(std::ostream& ost, ObjectFile file);
	std::vector<int> int_at(int i);
	std::string str_at(int i);
private:
	void loadFile();
	std::string m_path;
	std::vector<std::string> m_strContaine;
	std::vector<std::vector<int>> m_containe;
};

#endif

