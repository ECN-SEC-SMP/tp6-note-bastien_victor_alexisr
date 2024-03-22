#include "player.hpp"

// Constructeur
Player::Player(std::string _name, int _money, int _position) : name(_name), money(_money), position(_position) {}

// Méthodes pour accéder et modifier les attributs
std::string Player::getName() const {
    return name;
}

int Player::getMoney() const {
    return money;
}

int Player::getPosition() const {
    return position;
}

void Player::setMoney(int _money) {
    money = _money;
}

void Player::removeProperty(Property* Property) {
    for (auto it = Properties.begin(); it != Properties.end(); ++it) {
        if (*it == Property) {
            Properties.erase(it);
            break;
        }
    }
}

// Méthode pour buy une propriété
void Player::buyProperty(Property* Property) {
    if (money >= Property->getRent()) {
        money -= Property->getRent();
        Property->setOwner(this);
    }
}

// Méthode pour payer un loyer
void Player::payRent(int rent) {
    money -= rent;
}

// Méthode pour afficher les informations du Player
void Player::renderInfos() const {
    std::cout << "name du Player : " << name << std::endl;
    std::cout << "money : " << money << std::endl;
    std::cout << "Position sur le plateau : " << position << std::endl;
    std::cout << "Propriétés possédées :" << std::endl;
    for (const auto& Property : Properties) {
        std::cout << "   - " << Property->getName() << std::endl;
    }
}
