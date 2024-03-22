#include "property.h"

// Constructeur
Property::Property(std::string _name, int _price) : name(_name), rent(_price), owner(nullptr) {}

// Méthodes pour accéder aux attributs
std::string Property::getName() const {
    return name;
}

int Property::getRent() const {
    return rent;
}

Player* Property::getOwner() const {
    return owner;
}

// Méthode pour définir le propriétaire de la propriété
void Property::setOwner(Player* _owner) {
    owner = _owner;
}
