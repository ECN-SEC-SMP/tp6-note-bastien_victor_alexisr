#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include "player.hpp" // Si nécessaire

class Player; // Déclaration anticipée de la classe Player

class Property {
private:
    std::string name;        // Nom de la propriété
    int rent;               // Prix d'achat de la propriété
    Player* owner;   // Propriétaire de la propriété

public:
    // Constructeur
    Property(std::string _name, int _rent);

    // Méthodes pour accéder aux attributs
    std::string getName() const;
    int getRent() const;
    Player* getOwner() const;

    // Méthode pour définir le propriétaire de la propriété
    void setOwner(Player* _owner);
};

#endif // PROPERTY_H
