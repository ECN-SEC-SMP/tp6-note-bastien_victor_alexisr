#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>
#include "property.h" // Inclure le fichier d'en-tête de la classe Property si nécessaire

class Player {
private:
    std::string name;            // name du Player
    int money;                 // money (mono) du Player
    int position;               // Position du Player sur le plateau
    std::vector<Property*> Properties;  // Liste des propriétés possédées par le Player

public:
    // Constructeur
    Player(std::string _name, int _money, int _position);

    // Méthodes pour accéder et modifier les attributs
    std::string getName() const;
    int getMoney() const;
    int getPosition() const;
    void setMoney(int _money);

    // Méthodes pour gérer les propriétés du Player
    void buyProperty(Property* Property);
    void removeProperty(Property* Property);

    // Méthode pour payer un loyer
    void payRent(int rent);

    // Méthode pour afficher les informations du Player
    void renderInfos() const;
};

#endif // PLAYER_H
