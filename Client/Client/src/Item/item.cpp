#include <Item/item.h>

item::item() {}

item::item(int ID, std::string name, TypeObj typeObj) {
	m_ID = ID;
	m_typeObj = typeObj;
	m_name = name;
	// TODO
	// Initialise les texutres en fonction de l'ID
}

item::~item() {}

int item::getID() {	return m_ID; }
TypeObj item::getTypeObj() const { return m_typeObj; }
std::string item::getName() const { return m_name; }

void item::setID(int ID) {
	m_ID = ID;
	// TODO
	// Re-initialise les texutres en fonction de l'ID
}

void item::setTypeObj(TypeObj type) {
	m_typeObj = type;
}

void item::setName(std::string name) {
	m_name = name;
}

void item::setPosItem(sf::Vector2f pos) {
	m_sprite.setPosition(pos);
}

void item::draw(sf::RenderWindow& screen) {
	screen.draw(m_sprite);
}

void item::inPacket(sf::Packet& packet) {
	packet << m_ID << m_name << m_typeObj;
}

sf::Packet& operator<<(sf::Packet& packet, item& item_) {
	packet << item_.getID() << item_.getName() << static_cast<int>(item_.getTypeObj());
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, item& item) {
	int ID, type;
	std::string name;
	packet >> ID >> name >> type;
	item.setID(ID);
	item.setTypeObj(static_cast<TypeObj>(type));
	return packet;
}

std::ostream& operator<<(std::ostream &os, item& item_) {
	item_.write();
	return os;
}

void item::write() {
	std::cout << "Type d'object: " << static_cast<int>(m_typeObj) << std::endl;
	std::cout << "ID: " << m_ID << std::endl;
	std::cout << "Name: " << m_name << std::endl;
}