#ifndef CARTE_H
#define CARTE_H

#include <string>
#include "player.hpp" 

class Player; 

class Card {
protected:
    std::string text;  // Text of the card

public:
    // Constructor
    Card(std::string _text);

    // How to apply the card effect to the player
    virtual void appliedEffect(Player* player) = 0;
};

class ChanceCard : public Card {
public:
    // Constructor
    ChanceCard(std::string _text);

    // How to apply the Chance card effect to the player
    void appliedEffect(Player* player) override;
};

class CommunityChestCard : public Card {
public:
    // Constructor
    CommunityChestCard(std::string _text);

    // How to apply the Community card effect to the player
    void appliedEffect(Player* player) override;
};


#endif // CARTE_H