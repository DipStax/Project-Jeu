#include <Gestion/ObjectFile.h>
#include <Gestion/GestPersoGen.h>

ObjectFile::ObjectFile(std::string path) {
	m_path = path;
	this->loadFile();
}


ObjectFile::~ObjectFile() {}

void ObjectFile::newFile(std::string path) {
	m_path = path;
	this->loadFile();
}

std::ostream& operator<<(std::ostream& ost, ObjectFile file) {
	for (auto& line : file.m_containe) {
		for (auto& val : line) {
			ost << val << " ";
		}
		ost << std::endl;
	}
	return ost;
}

std::vector<int> ObjectFile::int_at(int i) {
	return m_containe.at(i);
}

std::string ObjectFile::str_at(int i) {
	return m_strContaine.at(i);
}


void ObjectFile::loadFile() {
	std::vector<std::vector<std::string>> wordList = gpg::genWord(m_path);
	if (wordList.size() > 2) {
		wordList.erase(wordList.begin(), wordList.begin() + 1);
		for (auto& line : wordList) {
			if (!line.empty()) {
				m_strContaine.push_back(line[0]);
				line.erase(line.begin());
			}
		}
		for (auto& line : wordList) {
			std::vector<int> intList;
			for (auto& word : line) {
				intList.push_back(std::stoi(word));
			} 
			m_containe.push_back(intList);
		}
	}
}